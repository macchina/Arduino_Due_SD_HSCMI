/*  Dumpdata: Serial to SD - reading from SerialUSB (Arduino Due Native port) and writing to file
 *
 *  Written in July 2016 by Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu) for Macchina LLC
 *
 *  To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
 *
 *  You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
 *  
 *  Using modified Arduino_Due_SD_HSCMI library (https://github.com/macchina/Arduino_Due_SD_HSMCI) from Github user JoaoDiogoFalcao (https://github.com/JoaoDiogoFalcao/Arduino_Due_SD_HSCMI)
 *  
 *  CAUTION!
 *  To run this code, please compile and upload code to your board. When code is uploaded, please run Serial Terminal as quick as plausible.
 *  
 *  Developed against Arduino IDE 1.6.9
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
