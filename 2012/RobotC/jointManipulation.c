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

tMotor whichMotor = motorI;
bool lastOrangeButton = false;
/*===================================================================================================================*/
void updateDisplay() {

   if (whichMotor == motorI) {
      nxtDisplayCenteredBigTextLine(3, "%s", "SHOULDER");
   } else if (whichMotor == motorJ) {
      nxtDisplayCenteredBigTextLine(3, "%s", "ELBOW");
   } else {
      nxtDisplayCenteredBigTextLine(3, "%s", "???");
   }
   nxtDisplayTextLine(6, "%d", nMotorEncoder[motorI]);
}
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
   updateDisplay();
}
/*===================================================================================================================*/
task main() {

   initializeRobot();
   while(true) {
      if (nNxtButtonPressed == 3) {
         if (whichMotor == motorI) {
            whichMotor = motorJ;
            PlayImmediateTone(440,10);
         } else {
            whichMotor = motorI;
            PlayImmediateTone(350,10);
         }
         while (nNxtButtonPressed == 3) {
            wait1Msec(2);
         }
      }
      updateDisplay();
      if (nNxtButtonPressed == 1) {
         motor[whichMotor] = 10;
      } else if (nNxtButtonPressed == 2) {
         motor[whichMotor] = -10;
      }else {
         motor[motorI] = 0;
         motor[motorJ] = 0;
      }

      wait1Msec(2);
   }
}
/*===================================================================================================================*/