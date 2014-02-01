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

#include "AutoLibrary.c"

task main()
{
	while(true)
	{
		nxtDisplayTextLine(4, "IR = %d", SensorRaw(IRSensor));
	}
}
/*
	int distance = 5000;
	nMotorEncoder[motorRight] = 0;
	while(nMotorEncoder[motorRight] < 1000)
	{
		motor[motorRight] = nMotorEncoder[motorRight] / 10 + 10;
		motor[motorLeft] = nMotorEncoder[motorRight] / 10 + 10;
	}
	while(nMotorEncoder[motorRight] < distance - 100)
	{
		motor[motorRight] = 100;
		motor[motorLeft] = 100;
	}
	while(nMotorEncoder[motorRight] < distance)
	{
		motor[motorRight]	= distance - nMotorEncoder[motorRight];
		motor[motorLeft] = distance - nMotorEncoder[motorRight];
	} */
