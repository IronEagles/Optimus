/*===========================================================================*/
/*                                                                           */
/*      First Tech Challenge - team 3708, Iron Eagles "Optimus"              */
/*                                                                           */
/*                                                                           */
/*                                   ROBOT ARM GEOMETRIES:                   */
/*             //*\\                                                         */
/*         /  //Qe \\   \            P(0,0) - position of the shoulder       */
/*       LH  //     \\   LU          P(x,y) - position of the wrist          */
/*       /  //       \\   \          LH - length of the humerus (constant)   */
/*         //         \\             LU - length of the ulna    (constant)   */
/*        //           \\            lR - length of reach = (x**2+y**2)^2    */
/*       //             \\ Qw        Qs - shoulder angle, from X axis        */
/* (0,0) * Qs  -lR-      *==OO       Qe - elbow angle, inside angle          */
/*     [==]---           P(x,y)      Qw - wrist angle, from the ulna         */
/*     [==]                                                                  */
/*     [==]                                                                  */
/*===========================================================================*/
/*                                                                           */
/* shoulder joint: 9-to-1 gear ratio                                         */
/* elbow joint: 6-to-1 gear ratio                                            */
/* the shoulder is parked at about -7690 ticks from the zero-degree point    */
/*                                                                           */
/* shaft encoders: 1440 ticks per revolution                                 */
/* ticks-per-second-per-motorset is around 25-30.  e.g. if you want a motor  */
/* to turn at a rate of roughly 50 to 60 encoder ticks per second, set the   */
/* motor speed to 20.                                                        */
/*                                                                           */
/*                                                                           */
/*===========================================================================*/

#ifndef ARM_KINETICS_C
#define ARM_KINETICS_C

// state the lengths of the arm segments in inches
#define HUMER 17.6
#define ULNA 15.7
#define FLOORLEVEL -8.5
#define MAXREACH  (0.95*(HUMER + ULNA))

// angle of shoulder joint when it is parked, in radians (is about 215 degrees)
#define QS_PARKED 3.752

// gear ratios for the shoulder and the elbow joints
#define QS_GEAR 9.0
#define QE_GEAR 6.0

// All the arm-related numbers stuffed in a box for easy handling.  units are
// inches and radians.
typedef struct {
   float qe;
   float qs;
   float qw;
   float x;
   float y;
} armState;

// 2D rectangular coordinates
typedef struct {
   float x;
   float y;
} rectangular;

// 2D polar coordinates
typedef struct {
   float r;
   float q;
} polar;

/* google "law of cosines" for general triangle calculations.                */
/*===========================================================================*/
/* converts rectangular coordinates to polar coordinates, with the range of  */
/* the calculated q being:  -PI/2 < q <= 3*PI/2                              */
/* because this range works nicely for the robot arm calculations            */
/* see: http://en.wikipedia.org/wiki/Polar_coordinate_system                 */
/*                                                                           */
void rectToPolar(polar &p, rectangular &r) {

   p.r = sqrt(r.x * r.x + r.y * r.y);
   if (r.x == 0.0) {                           // if x is zero, can't use atan
      if (r.y > 0.0) {                         // so we set q based on which
         p.q = 0.5 * PI;                       // way y is pointing.
      } else if (r.y < 0.0) {
         p.q = 1.5 * PI;
      } else {
         p.q = 0.0;
      }
   } else {                                    // x is non-zero, but the calc
      p.q = atan(r.y / r.x);                   // of q depends on quadrant
      if (r.x < 0.0) {
         p.q += PI;
      }
   }
}
/*===========================================================================*/
/* convert polar coordinates to rectangular coordinates (q in radians)       */
/*                                                                           */
void polarToRect(rectangular &r, polar &p) {
   r.x = p.r * cos(p.q);
   r.y = p.r * sin(p.q);
}
/*===========================================================================*/
/* bring an angle back into the expected range of -PI < q <= PI              */
/*                                                                           */
void normalizeAngle(float &angle) {
   while (angle <= -PI) {
      angle += 2.0 * PI;
   }
   while (angle > PI) {
      angle -= 2.0 * PI;
   }
}
/*===========================================================================*/
/* given the two joint angles, calculate the tilt of the wrist necessary to  */
/* keep the donut handler level.  Range is 0.0 to PI. (0 to 180 degrees)     */
/*                                                                           */
void solveWristAngle(armState &arm) {

   arm.qw = arm.qe + arm.qs - PI / 2.0;
   if (arm.qw < 0.0) {
      arm.qw = 0.0;
   } else if (arm.qw > PI) {
      arm.qw = PI;
   }
}
/*===========================================================================*/
/* given a position for the wrist, calculate the joint angles.               */
/*                                                                           */
void solveArmFromWristPos(armState &arm, rectangular rWrist) {

   polar pWrist;
   float qi, cosq;

   arm.x = rWrist.x;
   arm.y = rWrist.y;

   rectToPolar(pWrist, rWrist);

   // calculate the angle of the elbow joint
   cosq = (HUMER * HUMER + ULNA * ULNA - pWrist.r * pWrist.r) /
           (2.0 * HUMER * ULNA);
   if (cosq > 1.0) {
      arm.qe = 0.0;
   } else if (cosq < -1.0) {
      arm.qe = PI;
   } else {
      arm.qe = acos(cosq);
   }

   // calculate the part of the shoulder angle inside this triangle.
   if (pWrist.r == 0.0) {
      qi = 0.0;
   } else {
      cosq = (HUMER * HUMER + pWrist.r * pWrist.r - ULNA * ULNA) /
           (2.0 * HUMER * pWrist.r);
      if (cosq > 1.0) {
         qi = 0.0;
      } else if (cosq < -1.0) {
         qi = PI;
      } else {
         qi = acos(cosq);
      }
   }
   arm.qs = pWrist.q + qi;

   // this calculation keeps the donut handler level
   solveWristAngle(arm);
}
/*===========================================================================*/
/* given the joint angles, calculate the position of the wrist.  Check the   */
/* numbers before feeding sqrt() and acos().                                 */
/*                                                                           */
void solveArmFromAngles(armState &arm, float qShoulder, float qElbow) {

   polar pWrist;
   rectangular rWrist;
   float qi;
   float rsq, cosqi;

   arm.qs = qShoulder;
   arm.qe = qElbow;

   // use the angle of the elbow and the law of cosines to calculate the
   // distance from the shoulder joint to the wrist joint
   rsq = HUMER * HUMER + ULNA * ULNA - 2.0 * HUMER * ULNA * cos(qElbow);
   if (rsq <= 0.0) {
      pWrist.r = abs(HUMER - ULNA);
   } else {
      pWrist.r = sqrt(rsq);
   }
   // calculate the part of the shoulder angle inside this triangle.
   cosqi = (HUMER * HUMER + pWrist.r * pWrist.r - ULNA * ULNA) /
           (2.0 * HUMER * pWrist.r);
   if (abs(cosqi) >= 1.0) {
      qi = 0.0;
   } else {
      qi = acos(cosqi);
   }

   if (qElbow < 0.0) {                     // if the elbow is "hyper-extended"
      qi = -qi;
   }
   pWrist.q = qShoulder - qi;
   polarToRect(rWrist, pWrist);
   arm.x = rWrist.x;
   arm.y = rWrist.y;

   // this calculation keeps the donut handler level
   solveWristAngle(arm);
}
/*===========================================================================*/
/* this procedure forces the given x,y coordinate back into the range that   */
/* the robot arm is capable of moving within.                                */
/*                                                                           */
void constrainArmPos(rectangular &nextPos) {
	polar nextPosPol;
	rectToPolar(nextPosPol, nextPos);
	if(nextPosPol.r > MAXREACH) {
		nextPosPol.r = MAXREACH;
      polarToRect(nextPos, nextPosPol);
	}

	if(nextPos.y < FLOORLEVEL) {
		nextPos.y = FLOORLEVEL;
	}
	if(nextPos.x < 2.0) {
		if(nextPos.y < nextPos.x) {
			nextPos.x = 2.0;
		}else{
         if (nextPos.y < 2.0) {
            nextPos.y = 2.0;
         }
		}
	}
}
/*===========================================================================*/

#endif /* ARM_KINETICS_C */
