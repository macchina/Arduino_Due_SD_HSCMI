/*  FileManipulation - open/create, close, rename, delete file
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
