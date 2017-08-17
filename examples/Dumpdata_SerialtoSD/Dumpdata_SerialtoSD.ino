/*  Copyright (c) 2016 Macchina
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  DataLogger: non-due-pins and data logger
 *  
 *  Using modified Arduino_Due_SD_HSCMI library from Github user JoaoDiogoFalcao (https://github.com/JoaoDiogoFalcao/Arduino_Due_SD_HSCMI)
 *  
 *  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)
 *  
 *  CAUTION!
 *  To run this code, please compile and upload code to your board. When code is uploaded, please run Serial Terminal as quick as plausible.
 *  
 *  Arduino IDE 1.6.9
 *  RoboSap, Institute of Technology, July 2016
 *
 *  Dumpdata - Serial to SD: reading from SerilUSB (Arduino Due Native port)and writing to file
 *  
 *  Using modified Arduino_Due_SD_HSCMI library from Github user JoaoDiogoFalcao (https://github.com/JoaoDiogoFalcao/Arduino_Due_SD_HSCMI)
 *  
 *  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)
 *  
 *  CAUTION!
 *  To run this code, please compile and upload code to your board. When code is uploaded, please run Serial Terminal as quick as plausible if you want to debug it.
 *  
 *  Arduino IDE 1.6.9
 *  RoboSap, Institute of Technology, July 2016
 */

// Including Arduino_Due_SD_HSCMI library also creates SD object (MassStorage class)
#include <Arduino_Due_SD_HSMCI.h> // This creates the object SD


// We need to create FileStore object, we will be using it to open/create file and to close file.
FileStore FS;

void setup() {
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  // Check if there is card inserted
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
  FS.Init(); // Initialization of FileStore object for file manipulation
//------------------------------------------------------------------------------------------------------
/* Following code creates file "SerialRead" in dir "0:" and writes data from serial to it. 
   Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory or file with the same name. Code first checks if name is alredy used when is needed. */

// First, let us tidy up Serial in and Serial out buffers, this is optional
  SerialUSB.flush(); // Clear Serial out buffer
  // Clear Serial in buffer
  while(SerialUSB.available()>0){
    SerialUSB.read();
  }
  
  char message[] = "Serial Read\n";
  
  // Create/Open file "data"
  FS.CreateNew("0:","SerialRead");
  //FS.GoToEnd(); // Optional
  FS.Write(message);
  FS.Close();
}

void loop() {
  // Check SerialUSB Buffer and read string
  if(SerialUSB.available()>0){
    //String str = SerialUSB.readString() + "\n";
    char write_buffer = SerialUSB.read(); // We will write to file one byte at the time
//    SerialUSB.print(write_buffer); // use this for debugging

// Open file and write to it
    FS.Open("0:","SerialRead",true);
    FS.GoToEnd(); // We need to go the end of the file
    FS.Write(write_buffer); // Write one byte of data to the file
    FS.Close();  
  }   
  delay(25); // 0.025s delay, optional
}
