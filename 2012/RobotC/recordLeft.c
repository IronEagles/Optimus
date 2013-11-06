#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
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

//Arm motor direction and gear ratios are correct as of 1-12-2013
#define DEADZONE 8
#include "JoystickDriver.c"
#include "drivers/hitechnic-gyro.h"
#include "armKinetics.c"
#include "heading.c"
#include "holonomicBase1.c"
#include "coordinatedArm1.c"
#include "eaglesrecord.c"
// #include "flightLrecord.c"

void initializeRobot() {

	bFloatDuringInactiveMotorPWM = false;
	nMaxRegulatedSpeed12V = 500;              /* improves motor control */
	bNxtLCDStatusDisplay = true;
	disableDiagnosticsDisplay();
	eraseDisplay();
	ClearTimer(T2);
	getJoystickSettings(joystick);
	initializeBase();
	initializeArm();


}

task main() {
   initializeRobot();
   waitForStart();
   StartTask(heading);
   ClearTimer(T4);
   open_flight_record("flightL.txt");
   while(true) {
      getJoystickSettings(joystick);
      update_flight_record();
      updateArmMovement();
      if(joy1Btn(4) == 1) {
         nxtDisplayTextLine(6, "button  %d", joy1Btn(4));
         currHeading = 270.0;
      }
      updateBaseMovement();
      wait1Msec(20);
      if(joy2Btn(2) == 1){
         close_flight_record();
	 StopAllTasks();
      }
   }
}
