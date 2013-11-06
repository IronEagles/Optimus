#include "JoystickDriver.c"
//#include the driving program

//Include file to "handle" the Bluetooth messages.
//#include "drivers/HTMAG-driver.h"
//

TFileHandle flightDatFH;
//============================================================================
// remove old file, open new one and write the header
//
int open_flight_record(const string sFileName) {

   TFileIOResult nIoResult;
   int nFileSize = 15 * 1024;
   ClearTimer(T4);

   Delete(sFileName, nIoResult);
   OpenWrite(flightDatFH, nIoResult, sFileName, nFileSize);
   if (nIoResult != 0) {
      wait10Msec(50);
      StopAllTasks();
   }
   WriteText(flightDatFH, nIoResult, "int flight[][X]={\n"); //X=MotorNumber+ 1
   wait10Msec(5);
   return(0);
}
//============================================================================
// writes a final record with a negative timestamp, closes out the 2-D array
// and then closes the file itself.
//
int close_flight_record() {
   TFileIOResult nIoResult; //names the filehandle that watches for mistakes

   WriteText(flightDatFH, nIoResult, "{-1,0,0,0,0,0"); //negative timestamp will never be reached, 0s should be the number of motors
   WriteText(flightDatFH, nIoResult, ",0,0}};\n");		//computer accepts futility and stops trying
   Close(flightDatFH, nIoResult);											//Close up shop
   if (nIoResult != 0) {                     // if there was a problem in the inputs and outputs, "nIoResult" returns 1
      wait10Msec(50);
      StopAllTasks();												//Automatic kill code
      return(nIoResult);
   }
   wait1Msec(50); //time buffer
   return(0);
}
//============================================================================
void update_flight_record() {

   TFileIOResult nIoResult;

   static int      lastMotorE = 0;
   static int      lastMotorF = 0;
   static int      lastMotorJ = 0;
   static int      lastMotorG = 0;
   static int      lastMotorH = 0;
   static int			 lastMotorI = 0;
   string          str = "                                            ";


   if (motor[motorE] == lastMotorE          &&			//compare all the current values
       motor[motorF] == lastMotorF          &&			//"Is E the same as last I checked AND F the same as last I checked AND..."
       motor[motorG]  == lastMotorG         &&
       motor[motorH]  == lastMotorH 		  	&&
       motor[motorI] == lastMotorI	        &&
       motor[motorJ] == lastMotorJ)
 	 {
   	return;				//Yes? All of them? return to start
   }
	else							//No? Do the following
	{
   StringFormat(str, "{%d,", time1(T4));	// find the time
   WriteText(flightDatFH, nIoResult, str);//write it down
   StringFormat(str, "%d,", motor[motorE]);//What is the value of the motor?
   WriteText(flightDatFH, nIoResult, str);//Write it down
   StringFormat(str, "%d,", motor[motorF]);
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d,", motor[motorJ]);
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d,", motor[motorI]);
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d,", motor[motorG]);
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d,", motor[motorH]);
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d},\n", ServoValue[servo1]);
   WriteText(flightDatFH, nIoResult, str);
   }
   if (nIoResult != 0)
    {
      Close(flightDatFH, nIoResult);
      wait10Msec(50);
      StopAllTasks();
    }
   lastMotorE = motor[motorE];
   lastMotorF = motor[motorF];
   lastMotorG = motor[motorG];
   lastMotorH = motor[motorH];
   lastMotorI = motor[motorI];
   lastMotorJ = motor[motorJ];

}
