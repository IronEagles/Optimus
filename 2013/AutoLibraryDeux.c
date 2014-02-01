#include "drivers/hitechnic-gyro.h"
float currHeading = 0.0;

#define ENC_PER_INCH (1440.0) / (4.0 * PI)
#define POS_BASKET_ONE 24
#define POS_BASKET_TWO 10
#define POS_BASKET_THREE 21
#define POS_BASKET_FOUR 10
#define MOTOR_LEFT "LeftDrive"
#define MOTOR_RIGHT "RightDrive"


// A better accelerate would take a distance to accelerate over/ devide your distance(encoder counts) by speed and then bump up speed every
// certain amount of encoder counts
int interface ()
{
	int yournumber = 1;

	until(nNxtButtonPressed == 3)
	{
		nxtDisplayTextLine(1, "1: Foward Auto");
		nxtDisplayTextLine(2, "2: Backward Auto");
		nxtDisplayTextLine(3, "3: Fastest Auto");
		nxtDisplayTextLine(4, "Your Choice %d", yournumber);

		if(nNxtButtonPressed == 1)
		{
			yournumber --;
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 2)
		{
			yournumber ++;
			wait1Msec(300);
		}
	}
}

int timeinterface ()
{
	int yourtime = 0;

	until(nNxtButtonPressed == 3)
	{
		nxtDisplayTextLine(2, "How long before start?");
		nxtDisplayTextLine(4, "Time: %d", yourtime);

		if(nNxtButtonPressed == 1)
		{
			yourtime --;
		}
		if(nNxtButtonPressed == 2)
		{
			yourtime ++;
		}

	}
	return yourtime;
}
void accelerate(int initialSpeed = 20, int topSpeed = 100, int distance = 5) // initial speed, top speed, distance
{
	int rate = (distance * ENC_PER_INCH) / (topSpeed - initialSpeed);
	int initialRightEnc = nMotorEncoder[MOTOR_RIGHT];
	int initialLeftEnc = nMotorEncoder[MOTOR_LEFT];
	int newSpeed;
	newSpeed= initialSpeed;
		while(nMotorEncoder[MOTOR_RIGHT]<initialRightEnc+(int)(distance*ENC_PER_INCH)	|| nMotorEncoder[MOTOR_LEFT]>initialLeftEnc-(int)(distance*ENC_PER_INCH))
		{
			if(nMotorEncoder[MOTOR_RIGHT] > initialRightEnc + rate)
			{
				newSpeed = newSpeed + (topSpeed - initialSpeed);

			}
		}
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
void driveForward(int speed, int distance) //power, rate of acceleration, distance (inches)
{
	nMotorEncoder[MOTOR_RIGHT] = 0;
	nMotorEncoder[MOTOR_LEFT] = 0;
	accelerate();
	while(nMotorEncoder[MOTOR_RIGHT] < (int)(distance * ENC_PER_INCH) && nMotorEncoder[MOTOR_LEFT] > -(int)(distance * ENC_PER_INCH))
	{
		//OHHHH YEAHHHHHHH
	}
	motor[MOTOR_LEFT] = 0;
	motor[MOTOR_RIGHT] = 0;
	//accelerate(-10, 100, 0); //how to make it stop within distance?
}

void gyroTurn(int power, float turn)
{
	currHeading = 0.0;
	motor[MOTOR_LEFT] = power;
	motor[MOTOR_RIGHT] = -power;
	while(currHeading < (0.0+turn) || currHeading > (360.0-turn))
	{
		wait1Msec(20);
	}

	motor[MOTOR_LEFT] = 0;
	motor[MOTOR_RIGHT] = 0;

	wait1Msec(1000);
}

int driveSeekBasket()
{
	nMotorEncoder[MOTOR_RIGHT] = 0;
	nMotorEncoder[MOTOR_LEFT] = 0;
	while(nMotorEncoder[MOTOR_RIGHT] < (int)(POS_BASKET_ONE * ENC_PER_INCH) && nMotorEncoder[MOTOR_LEFT] > -(int)(POS_BASKET_ONE * ENC_PER_INCH))
	{
		accelerate(20, 100, POS_BASKET_ONE / 2);
		accelerate(100, 20, POS_BASKET_ONE / 2);
		motor[MOTOR_LEFT] = 0;
		motor[MOTOR_RIGHT] = 0;
	}
	if(checkIR(6))
		{
			return 1;
			break;
		}else{
			nMotorEncoder[MOTOR_RIGHT] = 0;
			nMotorEncoder[MOTOR_LEFT] = 0;
			while(nMotorEncoder[MOTOR_RIGHT] < (int)(POS_BASKET_TWO * ENC_PER_INCH) && nMotorEncoder[MOTOR_LEFT] > -(int)(POS_BASKET_TWO * ENC_PER_INCH))
			{
				accelerate(20, 100, POS_BASKET_TWO / 2);
				accelerate(100, 20, POS_BASKET_TWO / 2);
				motor[MOTOR_LEFT] = 0;
				motor[MOTOR_RIGHT] = 0;
			}
		}
	if(checkIR(5))
	{
		return 2;
		break;
	}else{
		nMotorEncoder[MOTOR_RIGHT] = 0;
		nMotorEncoder[MOTOR_LEFT] = 0;
		while(nMotorEncoder[MOTOR_RIGHT] < (int)(POS_BASKET_THREE * ENC_PER_INCH) && nMotorEncoder[MOTOR_LEFT] > -(int)(POS_BASKET_THREE * ENC_PER_INCH))
			{
				accelerate(20, 100, POS_BASKET_THREE / 2);
				accelerate(100, 20, POS_BASKET_THREE / 2);
				motor[MOTOR_LEFT] = 0;
				motor[MOTOR_RIGHT] = 0;
			}
	}
	if(checkIR(5))
	{
		return 3;
		break;
	}else{
		nMotorEncoder[MOTOR_RIGHT] = 0;
		nMotorEncoder[MOTOR_LEFT] = 0;
		while(nMotorEncoder[MOTOR_RIGHT] < (int)(POS_BASKET_FOUR * ENC_PER_INCH) && nMotorEncoder[MOTOR_LEFT] > -(int)(POS_BASKET_FOUR * ENC_PER_INCH))
			{
				accelerate(20, 100, POS_BASKET_FOUR / 2);
				accelerate(100, 20, POS_BASKET_FOUR / 2);
				motor[MOTOR_LEFT] = 0;
				motor[MOTOR_RIGHT] = 0;
			}
	}
	return 4;
}

void forwardRamp()
{

}

void backwardRamp()
{

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
