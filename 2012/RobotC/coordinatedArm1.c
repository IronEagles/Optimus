int armSwitch = 0;

void initializeArm() {
   nMotorEncoder[motorI] = 0;
   nMotorEncoder[motorJ] = 0;
   motor[motorI] = 0;
   motor[motorJ] = 0;
}
/*===================================================================================================================*/
/*  displays arm angles in degrees, for debugging purposes.                                                          */
/*                                                                                                                   */
void displayArmAngles(armState &arm) {

   nxtDisplayTextLine(2, "qS: %.3f", arm.qs * 180 / PI);
   nxtDisplayTextLine(3, "qE: %.3f", arm.qe * 180 / PI);
   nxtDisplayTextLine(4, "qW: %.3f", arm.qw * 180 / PI);
}
/*===================================================================================================================*/
void readArmAngles(float &Qs, float &Qe) {
   // Qs = 2.0 * PI / (9.0 * 1440.0) * (float)(nMotorEncoder[motorI] + 7625);
   Qs = QS_PARKED + 2.0 * PI * (float)(nMotorEncoder[motorI]) / (1440.0 * QS_GEAR);
   Qe = 2.0 * PI * (float)(nMotorEncoder[motorJ]) / (1440.0 * QE_GEAR);
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

	if(joy2Btn(1) == true) {
		armSwitch = 1;
	}
	if(joy2Btn(3) == true) {
		armSwitch = -1;
	}
   if(abs(joystick.joy2_x1) > 6) {
      if(armSwitch == 1){
			deltaX = -0.015 * (float)(joystick.joy2_x1);
		}else{
			deltaX = 0.015 * (float)(joystick.joy2_x1);
		}
   } else {
      deltaX = 0.0;
   }
   if(abs(joystick.joy2_y1) > 6) {
      deltaY = 0.015 * (float)(joystick.joy2_y1);
   } else {
      deltaY = 0.0;
   }
   readArmAngles(qs, qe);
   solveArmFromAngles(thisArm, qs, qe);
   nextPos.x = thisArm.x + deltaX;
   nextPos.y = thisArm.y + deltaY;
   constrainArmPos(nextPos); // keep the target position within reach
   solveArmFromWristPos(nextArm, nextPos);
   if (nextArm.qs > thisArm.qs && nextArm.qs > QS_PARKED) {
      deltaQs = 0.0;
   } else {
      deltaQs = nextArm.qs - thisArm.qs;
   }
   if (nextArm.qe < thisArm.qe && nextArm.qe < 0.0) {
      deltaQe = 0.0;
   } else {
      deltaQe = nextArm.qe - thisArm.qe;
   }
   driveShoulder = (int)(deltaQs / 5.0 * 1440.0 * QS_GEAR / 2.0 / PI);
   driveElbow = (int)(deltaQe /5.0 * 1440.0 * QE_GEAR / 2.0 / PI);
   motor[motorI] = driveShoulder;
   motor[motorJ] = driveElbow;

   // automatic upward orientation of the wrist, plus driver control of offset
   // displayArmAngles(thisArm);
   int offset;
   if(armSwitch == 1){
      offset = -joystick.joy2_x2 / 3;
   } else {
      offset = joystick.joy2_x2 / 3;
   }
   if(joy2Btn(7) == 1) {
      offset += 40;
   }
   servoTarget[servo1] = (int)((thisArm.qw * 255 / PI) + offset);
}
/*===================================================================================================================*/

void updateArmMovement() {
   coordinatedArmControl();
}
