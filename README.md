## SD HSMCI for Macchina M2
Libraries and Examples for Macchina M2 HSMCI (High Speed MultiMedia Card Interface). Provides faster read/write to SD cards while freeing up SPI interface.

#### Install

1. Download the files
2. Move the folder `Arduino_Due_SD_HSMCI` to your Arduino Libraries

#### Storage manipulation

* The `SD` object will be created on `#include <Arduino_Due_SD_HSMCI.h>`
* Use `SD.MakeDirectory` to create a directory

#### Creating a file

* Create a new FileStore with `FileStore * f = new FileStore()`
* Initiate the File pointer with `f->Init()`
* Open the File Structure with `f->Open([DIRECTORY], [FILENAME], [FILE_WRITE | FILE_READ])`
* Write with `f->Write([BUFFER], [LENGTH]);`
* Close `f->Close()`

#### EXAMPLES

There are 6 example sketches included in Arduino_Due_HSMCI-master Library. List and description of examples in order of complexity:

* `DirManipulation` creates new directory, rename directory and delete directory from SD card
* `FileManipulation` creates new file, open/close file, rename file and delete file
* `FileList` creates files and writes raw data to them, checks writing times and creates a list of files on SD card
* `Datalogger_dif` creates new file, reads GPIO and log data to SD card
* `Dumpdata_SerialtoSD` creates new file than reads from SerialUSBand writes to the file
* `Dumpdata_SDtoSerial` creates new file with raw data than reads from file and print to SerialUSB

#### DEBUG

HSMCI library has the Debug option which can be enabled (DEFAULT) or disabled. To change that, please open `Arduino_Due_SD_HSMCI.h` and change constant `SD_DEBUG` to “true” (enabled) or false (disabled).
