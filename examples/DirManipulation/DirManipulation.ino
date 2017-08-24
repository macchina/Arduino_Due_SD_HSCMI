/*  DirManipulation - create, rename and delete directory
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
#include <Arduino_Due_SD_HSMCI.h>


void setup(){
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
//------------------------------------------------------------------------------------------------------
/* Following code creates directory "TestDir", than renames it to "DirFiles" and deletes it. 
   This is made in setup function since we want to do that once. Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory with the same name. Code first checks if name is alredy used. */

  // Check if TestDir already exists; if so, do not create directory TestDir
  if(!(SD.PathExists("0:TestDir"))){ // Need to enter path and not dir name.
     // Create Directory
     SD.MakeDirectory("TestDir"); // Make your directory named TestDir.
  }
 
  // Check if Directory Files alredy exist; if so, then do not rename TestDir
  if(!(SD.PathExists("0:Files"))){ // Need to enter path and not dir name.
    // Rename directory
    SD.Rename("TestDir","Files"); // Rename "TestDir" to "Files"
  }

  // Check if Files exists; if so, delete it
  if(SD.PathExists("0:Files")){
    // Delete directory
    SD.Delete("0:", "Files"); // Delete directory "Files" in root directory "0:"
  }
  
  // Make new directory "Test" and then directory "HSCMI" in that directory.
  if(!(SD.PathExists("0:Test"))){
    // Create Directory
    SD.MakeDirectory("Test"); // Make your directory named TestDir.
     // Make "HSCMI" dir in "Test"; check if "0:Test/HSCMI" doesn't alredy exists.
    if(!(SD.PathExists("0:Test/HSCMI"))){
      SD.MakeDirectory("Test","HSCMI");
    }
  }
}

void loop() {
  // Nothing to do here.
}
