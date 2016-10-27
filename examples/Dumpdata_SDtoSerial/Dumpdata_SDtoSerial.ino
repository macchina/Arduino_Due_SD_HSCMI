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
 *  Dumpdata - SD to Serial: reading from SD and printing on SerialUSB (Arduino Due Native port)
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
#include <Arduino_Due_SD_HSCMI.h> // This creates the object SD


// We need to create FileStore object, we will be using it to open/create file and to close file.
FileStore FS;

// We need to create some dummy data for fil
char data[]="data "; // char array of unknown length

void setup() {
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  // Check if there is card inserted
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
  FS.Init(); // Initialization of FileStore object for file manipulation
//------------------------------------------------------------------------------------------------------
/* Following code creates file "SerialRead" in dir "0:" and writes data to it. Then file is reopened in read mode and data is dumped to SerialUSB.
   Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory or file with the same name. Code first checks if name is alredy used when is needed. */
// First, let us tidy up Serial in and Serial out buffers, this is optional
  SerialUSB.flush(); // Clear Serial out buffer
  // Clear Serial in buffer
  while(SerialUSB.available()>0){
    SerialUSB.read();
  }
  
  // Create/Open file "SerialRead"
  FS.CreateNew("0:","SerialRead");
  for(unsigned int j=0;j<10;j++){
    FS.Write(data);
  }
  FS.Close();

  
  FS.Open("0:","SerialRead",false);
  SerialUSB.print("Reading from file: ");
  FS.Seek(0); // Go to position 0 in file - beginning of the file
  int i=0; // counter so we know when to stop reading from file
  char b; // We will read one byte at the time
  while(i<FS.Length()){ // repeat this action until you reached the end of file
    FS.Read(b); // Read one byte from file and store it in "b"
    SerialUSB.print(b); // print "b" to serial
  }
  
}

void loop() {
  // Nothing to do here
}
