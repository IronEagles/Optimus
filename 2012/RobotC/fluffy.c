#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorE,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorF,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorG,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorH,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorI,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorJ,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+-+=+*/
/* 8^p :-) */

#include "JoystickDriver.c"
#include "armKinetics.c"

/*===================================================================================================================*/
void displayArmState(armState &arm, int lineNum = 1) {
   nxtDisplayTextLine(lineNum++, "XY: %.2f  %.2f", arm.x, arm.y);
   nxtDisplayTextLine(lineNum++, "QQ: %.1f  %.1f", arm.qs * 180 / PI, arm.qe * 180 / PI);
}
/*===================================================================================================================*/
// 9 is the shoulder gear ratio, 6 is the elbow gear ratio
void readArmAngles(float &Qs, float &Qe) {
   // 7625
   Qs = 2.0 * PI / (9.0 * 1440.0) * (float)(nMotorEncoder[motorI] + 7625);
   Qe = 2.0 * PI / (6.0 * 1440.0) * (float)(nMotorEncoder[motorJ] + 0);
}
/*===================================================================================================================*/
/* hardware and software initialization                                                                              */

void initializeRobot() {

   bFloatDuringInactiveMotorPWM = false;
   nMaxRegulatedSpeed12V = 500;              /* improves motor control */
   bNxtLCDStatusDisplay = true;
   disableDiagnosticsDisplay();
   eraseDisplay();
   ClearTimer(T1);
   nMotorEncoder[motorI] = 0;
   nMotorEncoder[motorJ] = 0;
   motor[motorI] = 0;
   motor[motorJ] = 0;
   getJoystickSettings(joystick);
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
   nextPos.x = thisArm.x + deltaX;
   nextPos.y = thisArm.y + deltaY;
   solveArmFromWristPos(nextArm, nextPos);
   if (nextArm.qs > thisArm.qs && nextArm.qs > 3.69) {
      deltaQs = 0.0;
   } else {
      deltaQs = nextArm.qs - thisArm.qs;
   }
   if (nextArm.qe < thisArm.qe && nextArm.qe < 0.0) {
      deltaQe = 0.0;
   } else {
      deltaQe = nextArm.qe - thisArm.qe;
   }
   driveShoulder = (int)(deltaQs / 5.0 * 1440.0 * 9.0 / 2.0 / PI);
   driveElbow = (int)(deltaQe /5.0 * 1440.0 * 6.0 / 2.0 / PI);
   motor[motorI] = driveShoulder;
   motor[motorJ] = driveElbow;
}
/*===================================================================================================================*/

task main() {

   int i = 0;

   initializeRobot();
// waitForStart();

   while(true) {
      getJoystickSettings(joystick);
      coordinatedArmControl();
      wait10Msec(2);
   }
}
/*===================================================================================================================*/
