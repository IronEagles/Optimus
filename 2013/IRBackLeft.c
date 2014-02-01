#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     ,               sensorTouch)
#pragma config(Sensor, S3,     IRsensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoStandard)

#include "JoystickDriver.c"
#include "AutoLibrary.c"

void initializeRobot()
{
	servo[servo6] = 0;
	bFloatDuringInactiveMotorPWM = false;
  return;
}

task main()
{
//Starting block; Pull forward, turn.
  initializeRobot();
	waitForStart();
	StartTask(heading, 50);
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoder[motorRight] = 0;
	driveDistance(30, -900);
	wait10Msec(50);
	gyroTurn(-30, 38);
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoder[motorRight] = 0;
	wait10Msec(50);
	int motorSpeed = -20;
	bool scored = false;
//Begin looking for IR

	while(nMotorEncoder[motorRight] > -6000 && scored == false)
	{
		nxtDisplayTextLine(2,"encod. %d", nMotorEncoder[motorRight]);
		if(motorSpeed > -100)
		{
			motor[motorRight] = motorSpeed;
			motor[motorLeft] = motorSpeed;
			motorSpeed = motorSpeed - 3;
			wait10Msec(5);
		}
		if(nMotorEncoder[motorRight] > -1000)
		{
			if(CheckIR(4))
			{
				motor[motorLeft] = 0;
				motor[motorRight] = 0;
				servoTarget(servo6) = 230;
				wait10Msec(50);
				scored = true;
			}
		}
		//-------------
		if(nMotorEncoder[motorRight] > -2750 && nMotorEncoder[motorRight] < -1000)
		{
			if(CheckIR(5))
			{
				motor[motorLeft] = 0;
				motor[motorRight] = 0;
				servoTarget(servo6) = 230;
				wait10Msec(50);
				scored = true;
			}
		}
		//----------------
		if(nMotorEncoder[motorRight] > -4500 && nMotorEncoder[motorRight] < -2750)
		{
			if(CheckIR(5))
			{
				motor[motorLeft] = 0;
				motor[motorRight] = 0;
				servoTarget(servo6) = 230;
				wait10Msec(100);
				scored = true;
			}
		}
		//--------------
		if(nMotorEncoder[motorRight] > -6000 && nMotorEncoder[motorRight] < -4500)
		{
			if(CheckIR(6))
			{
				motor[motorLeft] = 0;
				motor[motorRight] = 0;
				servoTarget(servo6) = 230;
				wait10Msec(100);
				scored = true;
			}
		}

	}
	servoTarget(servo6) = 30;
	while(nMotorEncoder[motorRight] > 750)
	{
		motor[motorLeft] = 100;
		motor[motorRight] = 100;
	}
	motor[motorLeft] = 0;
	motor[motorRight] = 0;
	gyroTurn(-70, 100);
	driveDistance(-100, 4000);
	gyroTurn(70, 90);
	driveDistance(-75, 6000);
	PlayTone(500, 500);
	wait10Msec(1000);

}
