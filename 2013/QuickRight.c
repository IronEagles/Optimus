#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     IRsensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     RightDrive,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Flagspinner,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Spinmotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     ShoulderMotor, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ElbowMotor,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#include "JoystickDriver.c"
#include "AutoLibrary.c"

task main()
{
	StartTask(heading, 50);
	wait1Msec(3);
	waitForStart();
	nMotorEncoder[LeftDrive] = 0;
	nMotorEncoder[RightDrive] = 0;
	driveDistance(-100, -720);
	wait10Msec(50);
	servoTarget(servo6) = 230;
	wait10Msec(100);
	servoTarget(servo6) = 30;
	driveDistance(-100, -1500);
	gyroTurn(-50, 70);
	driveDistance(-100, -4000);

}
