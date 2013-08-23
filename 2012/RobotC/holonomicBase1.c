
polar polarJoy;
rectangular rectangularJoy;

typedef struct {
   float e;
   float f;
   float g;
   float h;
} bassDrive;
/*===================================================================================================================*/

//This scales the joystick
int scaleJoystick(int raw) {
	if(abs((float)raw) < DEADZONE){
		raw = 0;
	}else if(raw < 0){
		raw = raw + DEADZONE;
	}else {
		raw = raw - DEADZONE;
	}
	return(raw);
}
/*===================================================================================================================*/
float quadResponse(int raw) {
   float quad = raw * abs(raw) / 128.0;
   return(quad);
}
/*===================================================================================================================*/

//initializes the motors and encoders to zero
void initializeBase() {
	nMotorEncoder(motorE) = 0;
	nMotorEncoder(motorF) = 0;
	nMotorEncoder(motorG) = 0;
	nMotorEncoder(motorH) = 0;
	motor(motorE) = 0;
	motor(motorF) = 0;
	motor(motorG) = 0;
	motor(motorH) = 0;

	HTGYROstartCal(GYRO);
}
/*===================================================================================================================*/

//calculates the raw power values for each motor
void calcBassDrive(bassDrive &bass) {

	float rotation = quadResponse(joystick.joy1_x2) * 75.0 / 128.0;

   // allow the driver controlling the arm to rotate the bot slowly
//   if (abs(quadResponse(joystick.joy2_x2)) > abs(rotation)) {
//      rotation = quadResponse(joystick.joy2_x2);
//   }
	bass.e = (polarJoy.r * sin(polarJoy.q)) + rotation;
	bass.f = (polarJoy.r * cos(polarJoy.q)) + rotation;
	bass.g = (polarJoy.r * -sin(polarJoy.q)) + rotation;
	bass.h = (polarJoy.r * -cos(polarJoy.q)) + rotation;
}
/*===================================================================================================================*/

// Decides what the largest joystick input is, and outputs a number from 0.0 to 100.0, the numerator of the scale
// factor used to keep the motor values within range.
float maxJoyInput() {

   int maximum = 0;

	if (abs(joystick.joy1_x1) > maximum) {
      maximum = abs(joystick.joy1_x1);
   }
	if (abs(joystick.joy1_x2) > maximum) {
      maximum = abs(joystick.joy1_x2);
   }
	if (abs(joystick.joy1_y1) > maximum) {
      maximum = abs(joystick.joy1_y1);
   }
//	if (abs(joystick.joy2_x2) > maximum) {
//    maximum = abs(joystick.joy2_x2);
// }
   return(quadResponse(maximum) * 100.0 / 127.0);
}
/*===================================================================================================================*/

//determines the denominator of the scale factor by finding the largest raw motor value
float maxBassDrive(bassDrive myBass) {
	float maxBass = 0.0;

	if (abs(myBass.e) > maxBass) {
      maxBass = abs(myBass.e);
   }
	if (abs(myBass.f) > maxBass) {
      maxBass = abs(myBass.f);
   }
	if (abs(myBass.g) > maxBass) {
      maxBass = abs(myBass.g);
   }
	if (abs(myBass.h) > maxBass) {
      maxBass = abs(myBass.h);
   }

	return(maxBass);
}
/*===================================================================================================================*/

//scales all of the raw values
void scaleBassDrive(bassDrive &bass, float scaleFactor) {
	bass.e = bass.e * scaleFactor;
	bass.f = bass.f * scaleFactor;
	bass.g = bass.g * scaleFactor;
	bass.h = bass.h * scaleFactor;

}
/*===================================================================================================================*/

//applies scaled values to motors
void applyBassDrive(bassDrive &myBass) {
	motor[motorE] = (int)myBass.e;
	motor[motorF] = (int)myBass.f;
	motor[motorG] = (int)myBass.g;
	motor[motorH] = (int)myBass.h;
}
/*===================================================================================================================*/
/*===================================================================================================================*/
/* this set of code provides a way for the arm controller to make small rotational tweaks to the robot */
bool tweakIdle = true;
task tweakRotateCCW() {
   motor[motorE] = -25; motor[motorF] = -25;  motor[motorH] = -25;
   wait10Msec(20);
   motor[motorE] = 0; motor[motorF] = 0; motor[motorG] = 0; motor[motorH] = 0;
   wait10Msec(10);
   tweakIdle = true;
}
task tweakRotateCW() {
   motor[motorE] = 25; motor[motorF] = 25; motor[motorH] = 25;
   wait10Msec(20);
   motor[motorE] = 0; motor[motorF] = 0; motor[motorG] = 0; motor[motorH] = 0;
   wait10Msec(10);
   tweakIdle = true;
}
void checkForBaseTweaking() {
   int buttons = joystick.joy2_Buttons;
   if (buttons & 16 && tweakIdle) {
      tweakIdle = false;
      StartTask(tweakRotateCCW);
   }
   if (buttons & 32 && tweakIdle) {
      tweakIdle = false;
      StartTask(tweakRotateCW);
   }
}
/*===================================================================================================================*/
/*===================================================================================================================*/

// Changes the speed and direction of the robot based on joystick inputs.
void updateBaseMovement() {
   bassDrive myBass;
	float maxJoystick, maxBase, scaleFactor;
	rectangularJoy.x = (float)scaleJoystick(joystick.joy1_x1);
	rectangularJoy.y = (float)scaleJoystick(joystick.joy1_y1);
	rectToPolar(polarJoy, rectangularJoy);

  // rotate what is considered "forward" counterclockwise by about 60 degrees
   polarJoy.q = (polarJoy.q - degreesToRadians(currHeading));

   calcBassDrive(myBass);

   // nxtDisplayTextLine(1, "Vec %.2f  %.2f", polarJoy.r, polarJoy.q * 180 / PI);
   // nxtDisplayTextLine(2, "Max %f", maxJoyInput());
  // nxtDisplayTextLine(3, "Curr = %f", currHeading);
   maxJoystick = maxJoyInput();
   maxBase = maxBassDrive(myBass);
   scaleFactor = maxJoystick / maxBase;  // scale the motor drives to maximum
   scaleBassDrive(myBass, scaleFactor);
   // nxtDisplayTextLine(4, "e %f", myBass.e);
   // nxtDisplayTextLine(5, "f %f", myBass.f);
   // nxtDisplayTextLine(6, "g %f", myBass.g);
   // nxtDisplayTextLine(7, "h %f", myBass.h);

	if (tweakIdle) {
      applyBassDrive(myBass);
   }
   checkForBaseTweaking();
}
