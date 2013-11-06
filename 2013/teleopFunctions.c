// ------------------------------------------------------------------------------ //
//	This is a library of functions that should be easily put into a program using //
//  the #include FILENAME.h and then calling the functions and giving valid 			//
//--------------------------------------------------------------------------------//

#define DEADZONE 10
//This function updates the motors with direct joystick input. The arguments are
//the joystick, and then the name of the motor you want it to affect.
void updateMotor(int joystickInput, tMotor oneMotor)
{
	if(joystickInput > DEADZONE)
  {
   	motor[oneMotor] = joystickInput
  }else{
  	motor[oneMotor] = 0;
	}
}

//toggleMotor requires a global variable
bool toggled = false;
//this function uses a button input and a motor input to toggle a motor on/off
void toggleMotor(int button, tMotor motorToggle)
{
	if(button == 1 && toggled == false)
	{
		motor[motorToggle] = 100;
		toggled = true;
	} else if (button == 1 && toggled == true) {
		motor[motorToggle] = 0;
		toggled = false;
	}
}

//This function uses simple mathematics to create a smoother driving
//experience with two axis values. Takes input axis, axis, motor, motor
void updateBase(int yAxis, int xAxis, tMotor RightDrive, tMotor LeftDrive)
{
	int scaleFactor = 100;
	if(abs(yAxis) > DEADZONE)
	{
		if(abs(xAxis) > DEADZONE)
		{
			if(xAxis < 0)
			{
				motor[RightDrive] = ((yAxis + xAxis) / 127.0) * scaleFactor;
				motor[LeftDrive] = ((yAxis) / 127.0) * scaleFactor;
			} else {
				motor[RightDrive] = (yAxis / 127.0) * scaleFactor;
				motor[LeftDrive] = ((yAxis - xAxis) / 127.0) * scaleFactor;
			}
		} else {
			motor[LeftDrive] = (yAxis / 127.0) * scaleFactor;
			motor[RightDrive] = (yAxis / 127.0) * scaleFactor;
		}
	}else {
		motor[LeftDrive] = -(xAxis / 127.0) * scaleFactor;
		motor[RightDrive] = (xAxis / 127.0) * scaleFactor;
	}
}

//this task monitors joystick inputs and if it finds no difference for a set amount of time
//it halts the robot until the override button is pressed
task checkConnection()
{



}
