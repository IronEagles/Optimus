// ------------------------------------------------------------------------------ //
//	This is a library of functions that should be easily put into a program using //
//  the #include FILENAME.h and then calling the functions and giving valid 			//
//--------------------------------------------------------------------------------//

#define DEADZONE 15
#define ENCSTOP 5000
//This function updates the motors with direct joystick input. The arguments are
//the joystick, and then the name of the motor you want it to affect.
void updateMotor(int joystickInput, tMotor oneMotor)
{
	if(abs(joystickInput) > DEADZONE)
  {
   	motor[oneMotor] = (joystickInput/2);
  }else{
  	motor[oneMotor] = 0;
	}
	wait10Msec(1);
}

//toggleMotor requires a global variable
bool toggled = false;
//this function uses a button input and a motor input to toggle a motor on/off
void toggleMotor(int button, tMotor motorToggle, int toggleValue)
{
	if(button == 1 && toggled == false)
	{
		motor[motorToggle] = toggleValue;
		toggled = true;
			wait10Msec(10);
	} else if (button == 1 && toggled == true) {
		motor[motorToggle] = 0;
		toggled = false;
			wait10Msec(10);
	}

}

void toggleServo(int button, TServoIndex servoName, int toggleValue)
{
	if(button == 1 && toggled == false)
	{
		servo[servoName] = toggleValue;
		toggled = true;
		wait10Msec(10);
	} else if (button == 1 && toggled == true) {
		servo[servoName] = 180;
		toggled = false;
		wait10Msec(10);
	}
}
//This function uses simple mathematics to create a smoother driving
//experience with two axis values. Takes input axis, axis, motor, motor
void updateBase(int yAxis, int xAxis, tMotor RightDrive, tMotor LeftDrive)
{
/*	int scaleFactor = 100;
	if(abs(yAxis) > DEADZONE)
	{
		if(abs(xAxis) > DEADZONE)
		{
			motor[RightDrive] = ((yAxis + (int)(xAxis/2)) / 256) * scaleFactor;
			motor[LeftDrive] = ((yAxis - (int)(xAxis/2)) / 256) * scaleFactor;
		} else {
			motor[LeftDrive] = (yAxis / 127) * scaleFactor;
			motor[RightDrive] = (yAxis / 127) * scaleFactor;
		}
	}else {
		motor[LeftDrive] = -(xAxis / 127) * scaleFactor;
		motor[RightDrive] = (xAxis / 127) * scaleFactor;
	}
	if(abs(yAxis) < DEADZONE && abs(xAxis) < DEADZONE)
	{
		motor[LeftDrive] = 0;
		motor[RightDrive] = 0;
	}
	*/
		if(abs(xAxis) > DEADZONE || abs(yAxis) > DEADZONE)
		{
			motor[RightDrive] = 100.0 * (yAxis + xAxis) / (127.0 + (float)abs(xAxis) ) ;
			motor[LeftDrive] = 100.0 * (yAxis - xAxis) / (127.0 + (float)abs(xAxis) ) ;
		} else {
			motor[LeftDrive] = 0;
			motor[RightDrive] = 0;
		}
}

//This task Runs the arm with an encoder stop at the top and a sensor stop at the bottom
void updateArm(int axisShoulder, int axisElbow, tMotor ShoulderMotor, tMotor ElbowMotor, //
																																			tSensors touchSensor)
{
	float scaleFactor = 1.0;
	if((int)nMotorEncoder[ShoulderMotor] > 5000)
	{
		scaleFactor = ((float)nMotorEncoder[ShoulderMotor] / 500.0);
	}else{
		scaleFactor = 1.0;
	}
	if(SensorValue(touchSensor) == 1)
	{
		if((axisShoulder) > 0)
		{
			updateMotor((int)(-axisShoulder / scaleFactor), ShoulderMotor);
		}else{
			motor[ShoulderMotor] = 0;
		}
	}else{
		if(nMotorEncoder[ShoulderMotor] > ENCSTOP)
		{
			if((axisShoulder) < 0)
			{
				updateMotor((int)(-axisShoulder / scaleFactor), ShoulderMotor);
			}else{
				motor[ShoulderMotor] = 0;
			}
		}else{
			updateMotor((int)(-axisShoulder / scaleFactor), ShoulderMotor);
		}
	}


}
//this task monitors joystick inputs and if it finds no difference for a set amount of time
//it halts the robot until the override button is pressed
task checkConnection()
{



}
