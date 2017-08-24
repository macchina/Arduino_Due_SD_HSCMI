/*  FileList - creates files and writes to them, creates list of files, speed test
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

// We need to create FileStore object, we will be using it to open/create file and to write to it and to close file.
FileStore FS;

// We need to create FileInfo object, we will be using it for creating list of files.
FileInfo aboutFile;

char data[]="data"; // char array of unknown length for data that will be written to files
float write_time=0; // to record 

void setup() {
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  // Check if there is card inserted
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
//------------------------------------------------------------------------------------------------------
/* Following code creates files "data1", "data2", "data3" and "data4" in dir "0:" and "data5", "data6", "data7" and "data8" in dir "test" and writes data to them. Alsi it performs speed test. 
 * Than it creates list of files on card. 
   This is made in setup function since we want to do that once. Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory or file with the same name. Code first checks if name is alredy used when is needed. */

  // Create files and write to them, if file already exist it will be overwritten
  FS.CreateNew("0:","data1"); // Create file in "0:" named "data1"
  for(unsigned int j=0;j<1000;j++){
    FS.Write(data); // Write array of chars to the opened file, do this 1000 times
  }
  write_time = FS.GetAndClearLongestWriteTime(); // Get longest write time of one block (one block of data = one byte)
  // Send write_time to Serial port, use terminal
  SerialUSB.print("Write Time: "); 
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close(); // Close file
  // Do the same for another 3 files
  FS.CreateNew("0:","data2");
  for(unsigned int j=0;j<2000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  FS.CreateNew("0:","data3");
  for(unsigned int j=0;j<3000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  FS.CreateNew("0:","data4");
  for(unsigned int j=0;j<4000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  // Make new directory and create another 4 files
  SD.MakeDirectory("test");
  FS.CreateNew("test","data5");
  for(unsigned int j=0;j<5000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  FS.CreateNew("test","data6");
  for(unsigned int j=0;j<6000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  FS.CreateNew("test","data7");
  for(unsigned int j=0;j<7000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();
  FS.CreateNew("test","data8");
  for(unsigned int j=0;j<8000;j++){
    FS.Write(data);
  }
  write_time = FS.GetAndClearLongestWriteTime();
  SerialUSB.print("Write Time: ");
  SerialUSB.print(write_time);
  SerialUSB.print("\n");
  FS.Close();

  // Creating a list of files
  SD.FindFirst("0:",aboutFile); // Find first file in "0:" and get information about it and save it to "abourFile", data is printed to Serial port if Debug is enabled
  while(SD.FindNext(aboutFile)){delay(500);} // Find every file in "0:" on SD card and save data to "aboutFile", data is printed to Serial port if Debug is enabled
  SD.FindFirst("test",aboutFile); // Find first file in "test" and get information about it and save it to "abourFile", data is printed to Serial port if Debug is enabled
  while(SD.FindNext(aboutFile)){delay(500);} // Find every file in "tet" on SD card and save data to "aboutFile", data is printed to Serial port if Debug is enabled
}

void loop() {
  // Nothing to do here.
}
