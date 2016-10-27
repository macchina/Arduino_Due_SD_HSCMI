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
 */

// Including Arduino_Due_SD_HSCMI library also creates SD object (MassStorage class)
#include <Arduino_Due_SD_HSCMI.h> // This creates the object SD

// Include SamNonDuePin.h library
#include "Arduino.h"
#include "SamNonDuePin.h"

// Copied from example for SamNonDuePin.h for your board
const int SW = PIN_EMAC_ERX1;     // Pushbutton SW2
const int Red =  32;         // the number of the LED pin

// We need to create FileStore object, we will be using it to open/create file and to close file.
FileStore FS;

// Variables
int sw_state = 0;
unsigned int i=0;

void setup() {
  delay(1000); // 1s delay so you have enough time to open Serial Terminal
  // Check if there is card inserted
  SD.Init(); // Initialization of HSCMI protocol and SD socket switch GPIO (to adjust pin number go to library source file - check Getting Started Guide)
  FS.Init(); // Initialization of FileStore object for file manipulation
//------------------------------------------------------------------------------------------------------
/* Following code creates file "data" in dir "0:" for logging raw data. Every time pushbutton is pushed, counter increment for 1 and number is logged into "data".
   Check Getting Started Guide for Debug options (Debug is enabled by default). 

   CAUTION!
   Code only works if there is no directory or file with the same name. Code first checks if name is alredy used when is needed. */

  char message[] = "\nCounter\n"; // Message at the beginnign of the file
  
  // Create/Open file "data"
  FS.CreateNew("0:","data"); // Create new file, if alredy exists it will be overwritten
  //FS.GoToEnd(); // Do not need when creating file because new file is opened and position 0
  FS.Write(message); // writing message
  FS.Close(); // we need to close file to store all the data that was written to it
   
  // Configure pushbuttons and LEDs
  pinMode(Red, OUTPUT);
  pinModeNonDue(SW,INPUT);
  digitalWrite(Red, LOW);
  }

void loop() {
  // This code is for logging data when button in pushed
  // Check if pushbutton is pushed
  sw_state = digitalReadNonDue(SW);
  if (sw_state == HIGH) {
    digitalWrite(Red, HIGH);     // turn LED OFF:
  }
  else {
    // LED on while pushbutton is pushed
    digitalWrite(Red, LOW);     // turn LED ON:
    // Increment counter
    i++;
    // Preapre buffer, write() method is accepting only array of chars, it is easier for us to create a string and then transform it into array of chars
    String str = "i= " + String(i) + "\n"; // creates a string
    char write_buffer[sizeof(str)]; // Creating array of char in length of our string
    str.toCharArray(write_buffer,sizeof(str)); // transform string to array of chars of strings's size
   // SerialUSB.print(write_buffer); // We can check what was created, SerilESB.print(.) uses serial buffer so we can print string or array of chars 
    // Write data to file.
    FS.Open("0:","data",true); // openning file
    FS.GoToEnd(); // Search for the end of file and write to it
    FS.Write(write_buffer); // write data to file
    FS.Close(); // to save data in file, we must close the file
  }
   
  delay(250); // 0.25s delay so there is not too much data   
}
