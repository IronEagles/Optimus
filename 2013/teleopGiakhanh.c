//Tele-op program
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
  return;
}

task main()
{
	initializeRobot();

  int speed_divisor = 0;
  int thresholdP = 10; //dead zone thresholds
  int thresholdN = -10; //dead zone thresholds

  waitForStart();   // wait for start of tele-op phase

  while (true)
  {

  getJoystickSettings(joystick);


	// Driving Turbo
 if (joy1Btn(5)== 1){
  	speed_divisor = 200;
	}else{
  	speed_divisor = 300;
  }

  if (abs(joystick.joy1_y1) < 10 & abs(joystick.joy1_x2) < 10) {
      motor[LeftDrive] = 0;
     motor[RightDrive] = 0;

  } else {
       motor[LeftDrive] = (- joystick.joy1_y1 + joystick.joy1_x2) * 100 / speed_divisor;
       motor[RightDrive] = (- joystick.joy1_y1 - joystick.joy1_x2) * 100 / speed_divisor;
  }


  //Shoulder Movement, not the elbow
  if((joystick.joy2_y1) > thresholdP)
    {
     motor[ShoulderMotor] = joystick.joy2_y1/3;
     nxtDisplayTextLine(7, "%d", nMotorEncoder[ShoulderMotor]);
    }

   if((joystick.joy2_y1) < thresholdN)
    {
     motor[ShoulderMotor] = joystick.joy2_y1/3;
     nxtDisplayTextLine(7, "%d", nMotorEncoder[ShoulderMotor]);
    }

   if((joystick.joy2_y1) < thresholdP && (joystick.joy2_y1) > thresholdN)
    {
     motor[ShoulderMotor] = 0;
    }

  //Elbow Movement
  if((joystick.joy2_y2) > thresholdP)
    {
     motor[ElbowMotor] = joystick.joy2_y2/3;
     nxtDisplayTextLine(7, "%d", nMotorEncoder[ElbowMotor]);
    }

   if((joystick.joy2_y2) < thresholdN)
    {
     motor[ElbowMotor] = joystick.joy2_y2/3;
     nxtDisplayTextLine(7, "%d", nMotorEncoder[ElbowMotor]);
    }

   if((joystick.joy2_y2) < thresholdP && (joystick.joy2_y2) > thresholdN)
    {
     motor[ElbowMotor] = 0;
    }

    //Spinner Control
 		if (joy1Btn(1)== 1)
 		{
 			motor[spinmotor] = 30;
 		}

 		else if (joy1btn(2)== 1)
 		{
 			motor(spinmotor) = -30;
 		}

 		else
 		{
 			motor(spinmotor) = 0;
 		}
	}
}
