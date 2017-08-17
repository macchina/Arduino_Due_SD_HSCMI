#include <Arduino_Due_SD_HSMCI.h> // This creates the object SD

void setup() {
  SD.Init();
	SD.MakeDirectory("TestDir");
}

void loop() {

}
