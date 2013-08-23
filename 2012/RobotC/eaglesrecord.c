#include "JoystickDriver.c"

//Include file to "handle" the Bluetooth messages.
//#include "drivers/HTMAG-driver.h"
//

TFileHandle flightDatFH;
//============================================================================
// remove old file, open new one and write the 2-D array header to it.
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
   WriteText(flightDatFH, nIoResult, "int flight[][8]={\n");
   wait10Msec(5);
   return(0);
}
//============================================================================
// writes a final record with a negative timestamp, closes out the 2-D array
// and then closes the file itself.
//
int close_flight_record() {
   TFileIOResult nIoResult;

   WriteText(flightDatFH, nIoResult, "{-1,0,0,0,0,0");
   WriteText(flightDatFH, nIoResult, ",0,0}};\n");
   Close(flightDatFH, nIoResult);
   if (nIoResult != 0) {                     // if there was a file I/O error
    //  PlaySoundFile("Woops.rso");
      wait10Msec(50);
      StopAllTasks();
      return(nIoResult);
   }
   wait10Msec(5);
   //PlaySoundFile("laser.rso");
   wait10Msec(50);
   return(0);
}
//============================================================================
void update_flight_record() {

   TFileIOResult nIoResult;

   static int      lastMotorE = 0;
   static int      lastMotorF = 0;
   static int      lastMotorJ = 0;
   static int      lastMotorI = 0;
	static int		lastwrist = 0;
   static int      lastMotorG = 0;
   static int      lastMotorH = 0;
   string          str = "                                            ";


   if (motor[motorE] == lastMotorE          &&
       motor[motorF] == lastMotorF          &&
       motor[motorJ] == lastMotorJ 					&&
       motor[motorI] == lastMotorI 		  		&&
       motor[motorG]  == lastMotorG         &&
       motor[motorH]  == lastMotorH &&
		ServoValue[servo1] == lastwrist)
 	 {
      return;
     }
	else
	{
   StringFormat(str, "{%d,", time1(T4));
   WriteText(flightDatFH, nIoResult, str);
   StringFormat(str, "%d,", motor[motorE]);
   WriteText(flightDatFH, nIoResult, str);
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
   if (nIoResult != 0) {
      Close(flightDatFH, nIoResult);
      wait10Msec(50);
      StopAllTasks();
   }
   lastMotorE = motor[motorE];
   lastMotorF = motor[motorF];
   lastMotorJ = motor[motorJ];
   lastMotorI = motor[motorI];
   lastMotorG = motor[motorG];
   lastMotorH = motor[motorH];
	lastwrist = ServoValue[servo1];
}
//============================================================================
