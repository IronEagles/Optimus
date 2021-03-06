#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorE,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorF,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorG,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorH,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorI,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorJ,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*===================================================================================================================*/
/* hardware and software initialization                                                                              */

int myServo;
/*===================================================================================================================*/
/*===================================================================================================================*/
void initializeRobot() {

   bFloatDuringInactiveMotorPWM = true;
   nMaxRegulatedSpeed12V = 500;              /* improves motor control */
   bNxtLCDStatusDisplay = true;
   // disableDiagnosticsDisplay();
   eraseDisplay();
   ClearTimer(T1);
   nMotorEncoder[motorI] = 0;
   nMotorEncoder[motorJ] = 0;
   motor[motorI] = 0;
   motor[motorJ] = 0;
   myServo = 127;
   servoTarget[servo1] = myServo;
}
/*===================================================================================================================*/
task main() {

   initializeRobot();
   while(true) {
      if (nNxtButtonPressed == 1) {
         myServo = myServo + 1;
         if (myServo > 255) {myServo = 255;}
      } else if (nNxtButtonPressed == 2) {
         myServo = myServo - 1;
         if (myServo < 0) {myServo = 0;}
      }
      servoTarget[servo1] = myServo;
      nxtDisplayCenteredBigTextLine(3, "%d", ServoValue[servo1]);
      wait10Msec(5);
   }
}
/*===================================================================================================================*/
