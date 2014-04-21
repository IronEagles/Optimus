#include "drivers/hitechnic-gyro.h"
float currHeading = 0.0;

#define ENC_PER_INCH (int)((1440.0) / (4.0 * PI))
#define POS_BASKET_ONE 24
#define POS_BASKET_TWO 10
#define POS_BASKET_THREE 21
#define POS_BASKET_FOUR 10
#define MOTOR_LEFT LeftDrive
#define MOTOR_RIGHT RightDrive


// --------- INTERFACE FUNCTION ----------------//
// This function polls the user for whether he wants
// to go backwards onto the ramp, or forwards on to the ramp
// thus helping us to strategize on the field
int interface ()
{
	int yournumber = 1;

	until(nNxtButtonPressed == 3)
	{
		eraseDisplay();
		//Print options to screen for user
		nxtDisplayBigTextLine(1, "1:Fwd");
		nxtDisplayBigTextLine(3, "2:Bckwd");
		nxtDisplayBigTextLine(5, "-> %d", yournumber);

		if(nNxtButtonPressed == 2)
		{
			yournumber --;
			wait1Msec(300);
		}
		if(nNxtButtonPressed == 1)
		{
			yournumber ++;
			wait1Msec(300);
		}
	}
	return yournumber;
}

//-----------------------------------------------------------------------------------------------------//
//This function does the same thing as the previous function, but asks for the desired wait time.
int timeinterface ()
{
	int yourtime = 0;


	until(nNxtButtonPressed == 3)
	{
		eraseDisplay();
		nxtDisplayBigTextLine(3, "Wait?");
		nxtDisplayBigTextLine(5, "-> %d", yourtime);

		if(nNxtButtonPressed == 2)
		{
			yourtime --;
			wait1Msec(400);
		}
		if(nNxtButtonPressed == 1)
		{
			yourtime ++;
			wait1Msec(400);
		}

	}
	return yourtime;
}


int beginInterface()
{
	int yournumber = 1;

	until(nNxtButtonPressed == 3)
	{
		eraseDisplay();
		//Print options to screen for user
		nxtDisplayTextLine(1, "1:N/A");
		nxtDisplayTextLine(2, "2:Wall");
		nxtDisplayTextLine(3, "3:Fast");
		nxtDisplayTextLine(4, "4:N/A");
		nxtDisplayTextLine(5, "-> %d", yournumber);

		if(nNxtButtonPressed == 2)
		{
			yournumber --;
			wait1Msec(200);
		}
		if(nNxtButtonPressed == 1)
		{
			yournumber ++;
			wait1Msec(200);
		}
		wait1Msec(50);
	}
	return yournumber;
}
//-----------------------------------------------------------------------------------------------------//
//This accelerates the robot from zero to 80

void accelerate() // initial speed, top speed, distance
{
	int speed = 0;
	while(speed < 80)  // from speed = 0 to 80
	{
		speed = speed + 10;
		//add speed
		motor[MOTOR_LEFT] = speed;
		motor[MOTOR_RIGHT] = speed + 2; // + 2 compensates for frictional force caused by unequal distribution of weight
		wait10Msec(5);
	}
}

//-----------------------------------------------------------------------------------------------------//
//accelerates the robot in a negative direction
void decelerate() // initial speed, top speed, distance
{
	int speed = 0;
	while(speed > -80)
	{
		speed = speed - 20;
		motor[MOTOR_LEFT] = speed - 2;
		motor[MOTOR_RIGHT] = speed;
		wait10Msec(5);
	}
}

//-----------------------------------------------------------------------------------------------------//
bool CheckIR(int irValue)
{
	if(SensorValue[IRsensor] == irValue)  //Only returns true if the IR sensor is reading the desired IR value
	{
		return(true); //
	}else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------------------------------//

void gyroTurn(int power, float turn)
{
	currHeading = 0.0; //Sets the initial angle to zero; Zeroes out the sensor.
	motor[MOTOR_LEFT] = power; //Supply input power to motors
	motor[MOTOR_RIGHT] = -power;
	while(currHeading < (0.0+turn) || currHeading > (360.0-turn)) //Until the absolute value of the sensor value is greater than 90
	{
		wait1Msec(20);
	}

	motor[MOTOR_LEFT] = 0;
	motor[MOTOR_RIGHT] = 0;

	wait1Msec(300);
}
//-----------------------------------------------------------------------------------------------------//
void driveTo(int distance)
{
		while(abs(nMotorEncoder[MOTOR_LEFT]) < (distance * ENC_PER_INCH) && abs(nMotorEncoder[MOTOR_RIGHT]) < (distance *ENC_PER_INCH))
		{
			//This function simply makes the robot supply power until the encoders reach an absolute value(Note, because it's absolute value
			// 	it doesn't drive distance, it drives to displacement from zero.)
		}
}
//-----------------------------------------------------------------------------------------------------//
void driveTo2(int distance) //THIS FUNCTION IS TRASH (keeping it just in case)
{
	 int abs_enc;
	  while(1) {
	  	 abs_enc = abs(nMotorEncoder[MOTOR_LEFT] + nMotorEncoder[MOTOR_RIGHT]) / 2;
	  	 if (abs_enc >= (distance * ENC_PER_INCH)) {
	  	    break;
	  	 }
	  }
}
//-----------------------------------------------------------------------------------------------------//
void forwardRamp() //Moved this code into Left/Right Deux programs because it's different for left/right sides
{

}

void backwardRamp()
{

}

task heading() //Turns the gyro-rotational force into a 'number of degrees turned' value.
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

void initialize()
{
	servoChangeRate[servo3] = 0;
	eraseDisplay();
	startTask(heading);
	nMotorEncoder[MOTOR_LEFT] = 0;
	nMotorEncoder[MOTOR_RIGHT] = 0;
}
