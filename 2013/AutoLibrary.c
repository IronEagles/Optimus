

#include "drivers/hitechnic-gyro.h"
float currHeading = 0.0;


void goToIR()
{
	nMotorEncoder[LeftDrive] = 0;
	nMotorEncoder[RightDrive] = 0;
	PlayTone(220, 15);
  motor[LeftDrive] = 30;
	motor[RightDrive] = 30;
	PlayTone(784, 15);
	while(SensorValue[IRsensor] != 4)  // infinite loop:
	{
  	nxtDisplayCenteredTextLine(2, "Sensor Value: %d", SensorValue[IRsensor]);  // display "Sensor Value: ##"
  	wait1Msec(10);  // Wait 100 milliseconds to help display correctly
	}

	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;
	PlayTone(784, 15);  // play a tone at a frequency of 784 for 150 milliseconds
}

bool CheckIR(int irValue)
{
	if(SensorValue[IRsensor] == irValue)  // infinite loop:
	{
		return(true);  // Wait 100 milliseconds to help display correctly
	}else
	{
		return(false);
	}
}

void FunctionToWall()
{
	//Score Autonomus goes here XD

	motor[LeftDrive] = 30;
	motor[RightDrive] = 30;
	while(nMotorEncoder[RightDrive] > 360 * 4 * 10.6 * -1)
	{
		nxtDisplayCenteredTextLine(4, "Encoder: %d", nMotorEncoder[RightDrive]);
		wait1Msec(10);
	}

	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;
}
void driveDistance(int power, int distance)
{
	if(power < 0)
	{
		distance = nMotorEncoder[RightDrive] + distance;
		if(power > 0)
		{
			while(nMotorEncoder[RightDrive] < distance )
			{
				motor[LeftDrive] = power;
				motor[RightDrive] = power;
			}
		}else
		{
			while(nMotorEncoder[RightDrive] > distance )
			{
				motor[LeftDrive] = power;
				motor[RightDrive] = power;
			}
		}
	}
	else
	{
		distance = nMotorEncoder[RightDrive] + distance;
		while(nMotorEncoder[RightDrive] < distance)
		{
			motor[LeftDrive] = power;
			motor[RightDrive] = power;
		}
	}

	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;
}

void gyroForward(int power, int distance)
{
	currHeading = 90.0;
	int driveHeading = currHeading;
	wait10Msec(100);
	nMotorEncoder[RightDrive] = 0;
	motor[RightDrive] = power;
	motor[LeftDrive] = power;
	while(distance < nMotorEncoder[RightDrive])
	{
		if(currHeading < (driveHeading - 1.0))
		{
			motor[RightDrive] = motor[RightDrive] - 1;
			motor[LeftDrive] = motor[LeftDrive] + 1  ;
		}
		if(currHeading > (driveHeading + 1.0))
		{
			motor[RightDrive] = motor[RightDrive] + 1 ;
			motor[LeftDrive] = motor[LeftDrive] - 1 ;
		}
		wait10Msec(10);
	}
}

void FunctionTurn()
{
	//90 Degree Turn
	motor[LeftDrive] = 30;
	motor[RightDrive] = -30;
}

void FunctionToWhiteLine()
{
	//White Line to Ramp
	int lightval = 0;

	motor[LeftDrive] = 30;
	motor[RightDrive] = 30;

	while(SensorValue(S2) <= (lightval + 4))
	{
  	nxtDisplayCenteredTextLine(1, "Sensor Value: %d", SensorValue(S2));  // display "Sensor Value: ##"
  	wait1Msec(10);  // Wait 100 milliseconds to help display correctly
	}

	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;
	PlayTone(784, 15);  // play a tone at a frequency of 784 for 150 milliseconds
	wait1Msec(1000);
}

void gyroTurn(int power, float turn)
{
	currHeading = 0.0;
	motor[LeftDrive] = power;
	motor[RightDrive] = -power;
	while(currHeading < (0.0+turn) || currHeading > (360.0-turn))
	{
		wait1Msec(20);
	}

	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;

	wait1Msec(1000);
}


task heading()
{
	float delTime = 0.0;
	float prevHeading = 0.0;
	float curRate = 0.0;
	HTGYROstartCal(GYRO);
   while (true) {
   	time1[T1] = 0;
    	curRate = HTGYROreadRot(GYRO);
    	if (abs(curRate) > 5) {
      	prevHeading = currHeading;
      	currHeading = prevHeading + (curRate * delTime);
      	if (currHeading > 360) currHeading -= 360;
      	else if (currHeading < 0) currHeading += 360;
    		}
    nxtDisplayTextLine(3, "Curr = %f", currHeading);
   	wait1Msec(5);
    	delTime = ((float)time1[T1]) / 1000;
    	//delTime /= 1000;

	}
}
