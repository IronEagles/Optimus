int lightCalibrate;
/* ----------------------------ULTRASONIC SENSOR ---------------------------------------------*/
float getAccelerationUS(string ultraSonic)
{
	int initialValue= sensorValue[ultraSonic];
	ClearTimer(T1);
	int initialTime= time1[T1];
	wait10Msec(100);
	int finalValue= sensorValue[ultraSonic];
	int finalTime= time1[T1];
	return (((float)finalValue - (float)initialValue) / (finalTime - initialTime)^2);
}

float getSpeedUS(string Ultrasonic)
{
	int initialValue= sensorValue[ultraSonic];
	ClearTimer(T1);
	wait10Msec(100);
	int finalValue= sensorValue[ultrasonic];
	int finalTime= time1[T1]
	return (((float)finalValue - (float) initialValue) / (finalTime - initialTime);
}

float getDistanceUS(string Ultrasonic)
{

}

/* --------------------------------LIGHT SENSOR ---------------------------------------------*/
