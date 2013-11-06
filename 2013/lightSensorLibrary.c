/* --------------------------------LIGHT SENSOR ---------------------------------------------*/
int lightCalibrate;
void calibrateLightSensor(string sensor)
{
	lightCalibrate = sensorValue(sensor);
}

bool isAboveThreshold(string sensor, int threshold)
{
	if((SensorValue(sensor) - lightCalibrate) > threshold)
	{
		return true;
	}else{
		return false;
	}
}

bool isBelowThreshold(string sensor, int threshold)
{
	if((SensorValue(sensor) - lightCalibrate) < -(threshold))
	{
		return true;
	}else{
		return false;
	}
}
