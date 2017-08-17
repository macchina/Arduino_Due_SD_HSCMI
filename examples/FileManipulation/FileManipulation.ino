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
 *  FileManipulation: open/create, close, rename, delete file
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
#include <Arduino_Due_SD_HSMCI.h> // This creates the object SD

// We need to create FileStore object, we will be using it to open/create file and to close file.
FileStore FS;

void setup() {
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  // Check if there is card inserted
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
  FS.Init(); // Initialization of FileStore class for file manipulation
//------------------------------------------------------------------------------------------------------
/* Following code creates fiel "mydata" in dir "0:", than it open/close it renames it to "data" and deletes it. 
   This is made in setup function since we want to do that once. Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory or file with the same name. Code first checks if name is alredy used when is needed. */

    // Create new file named "mydata"; it overwrites existing and it puts it open
    FS.CreateNew("0:","mydata"); // Creates and open new file named "mydata" in directory "0:"; when creating new, file is always open in "write" option
     // Close file named "mydata"
    FS.Close(); // File is saved, when it is closed. When closed, you can rename it or delete it.
    
    // Open file named "mydata"
    FS.Open("0:","mydata",true); // Open file in directory "0:"; third atribute is read (false) / write (true) 
    // Close file named "mydata"
    FS.Close(); // File is saved, when it is closed. When closed, you can rename it or delete it.

    // Rename file named "mydata" to "data"; check if there isn't file named "data" alredy created
    // Check is there is no file with file name "data"
    if(!(SD.FileExists("data"))){
       SD.Rename("mydata","data");
    }
    // Check for file "data" and then delete it
    if(SD.FileExists("data")){
        SD.Delete("0:","data"); //Delete file "data" in dir "0:"
     }
}

void loop() {
  // Nothing to do here.
}
