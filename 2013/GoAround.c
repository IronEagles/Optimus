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

task main()
{
	StartTask(heading, 50);
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoder[motorRight] = 0;
	driveDistance(100, 3500);
	gyroTurn(-30, 70);
	driveDistance(-100, -8000);
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoder[motorRight] = 0;
	gyroTurn(-30, 90);
	driveDistance(100, 1000);
	nMotorEncoder[motorLeft] = 0;
	nMotorEncoder[motorRight] = 0;
	gyroTurn(-30,90);
	while(true)
	{
		if(checkIR(5))
		{
			break;
		}
		if((nMotorEncoder(motorRight) > 7000) && checkIR(4))
		{
			break;
		}
		nxtDisplayTextLine(7, "%d", nMotorEncoder(motorRight);
		motor[motorLeft] = 28;
		motor[motorRight] = 28;
	}

	servoTarget(servo6) = 230;
	wait10Msec(100);
	servoTarget(servo6) = 30;
}
