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
 *  DirManipulation: create, rename and delete directory
 *  
 *  Using Arduino_Due_SD_HSCMI library from Github user JoaoDiogoFalcao (https://github.com/JoaoDiogoFalcao/Arduino_Due_SD_HSCMI)
 *  
 *  Author: Blaž Pongrac, RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)
 *  
 *  CAUTION!
 *  To run this code, please compile and upload code to your board. When code is uploaded, please run Serial Terminal as quick as plausible.
 *  
 *  Arduino IDE 1.6.9
 *  RoboSap, Institute of Technology, July 2016
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
