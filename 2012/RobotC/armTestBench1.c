
void initializeArm() {
   nMotorEncoder[motorI] = 0;
   nMotorEncoder[motorJ] = 0;
   motor[motorI] = 0;
   motor[motorJ] = 0;
}
/*===================================================================================================================*/
void readArmAngles(float &Qs, float &Qe) {
   Qs = 2.0 * PI / (9.0 * 1440.0) * (float)(nMotorEncoder[motorI] + 7625);
   Qe = 2.0 * PI / (2.0 * 1440.0) * (float)(nMotorEncoder[motorJ] + 0);
}
/*===================================================================================================================*/
/* direct control of joints.  left stick is shoulder, right stick is arm.                                            */
/*                                                                                                                   */
void manualJointControl() {

   if(abs(joystick.joy2_y1) > 6) {
      motor[motorI] = joystick.joy2_y1 / 2;
   } else {
      motor[motorI] = 0;
   }
   if(abs(joystick.joy2_y2) > 6) {
      motor[motorJ] = joystick.joy2_y2 / 4;
   } else {
      motor[motorJ] = 0;
   }
}
/*===================================================================================================================*/

void coordinatedArmControl() {

   float deltaQs, deltaQe;
   rectangular nextPos;
   float qs, qe;
   armState thisArm;
   armState nextArm;
   float deltaX, deltaY;
   int driveShoulder, driveElbow;

   if(abs(joystick.joy2_y1) > 6) {
      deltaX = 0.03 * (float)(joystick.joy2_y1);
   } else {
      deltaX = 0.0;
   }
   if(abs(joystick.joy2_y2) > 6) {
      deltaY = 0.03 * (float)(joystick.joy2_y2);
   } else {
      deltaY = 0.0;
   }
   readArmAngles(qs, qe);
   solveArmFromAngles(thisArm, qs, qe);
   nextPos.x = joystick.joy1_x1;
   nextPos.y = joystick.joy1_y1;
	nxtDisplayTextLine(1, "x = %f",nextPos.x);
	nxtDisplayTextLine(2, "y = %f",nextPos.y);
	constrainArmPos(nextPos);
	nxtDisplayTextLine(3, "Newx = %f",nextPos.x);
	nxtDisplayTextLine(4, "Newy = %f",nextPos.y);

}
/*===================================================================================================================*/

void updateArmMovement() {
   coordinatedArmControl();
}
