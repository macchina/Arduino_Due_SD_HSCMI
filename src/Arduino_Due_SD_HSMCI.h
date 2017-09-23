/****************************************************************************************************

PowerDueFirmware - SD Mass storage
Adapted from:
    RepRapFirmware - Platform: RepRapPro Ormerod with Duet controller
-----------------------------------------------------------------------------------------------------

Version 0.0.1
26 August 2016
Joao Diogo Falcao
Licence: MIT

Modified Tony Doust 26/08/2017 for use with Macchina M2 Tony Doust

****************************************************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

// Macchina M2 #define to use Macchine M2 specific defines in Macchina M2 variant files
#ifndef __MACCHINA_M2
#define __MACCHINA_M2	// Use Macchine M2 specific variant file defines
#endif

#define SD_DEBUG true

// Language-specific includes
#include <cctype>
#include <cstring>
#include <malloc.h>
#include <cstdlib>
#include <climits>

// Platform-specific includes
#include "Arduino.h"
#include "Configuration.h"
#include <SD_HSMCI/SD_HSMCI.h>

/**************************************************************************************************/


// Macro to give us the number of elements in an array
#define ARRAY_SIZE(_x)	(sizeof(_x)/sizeof(_x[0]))
// Macro to give us the highest valid index into an array i.e. one less than the size
#define ARRAY_UPB(_x)	(ARRAY_SIZE(_x) - 1)

// Macro to assign an array from an initializer list
#if __cplusplus >= 201103L
// This version relies on C++'11 features (add '-std=gnu++11' to your CPP compiler flags)
#define ARRAY_INIT(_dest, _init) {static const decltype(_dest) _temp = _init; memcpy(_dest, _temp, sizeof(_dest)); }
#else
// This version relies on a gcc extension that is available only in older compilers
#define ARRAY_INIT(_dest, _init) _dest = _init
#define nullptr		(0)
#endif

// File handling
#define FILE_WRITE true
#define FILE_READ false
#define MAX_FILES (10)
#define FILE_BUF_LEN (256)
#define WEB_DIR "0:/www/" 						// Place to find web files on the SD card
#define SYS_DIR "0:/sys/" 						// Ditto - system files
#define TEMP_DIR "0:/tmp/" 						// Ditto - temporary files

#define MAC_ADDRESS {0xBE, 0xEF, 0xDE, 0xAD, 0xFE, 0xED}


/****************************************************************************************************/

// Miscellaneous...

#define BAUD_RATE 115200 						// Communication speed of the USB if needed.
#define AUX_BAUD_RATE 57600						// Default communication speed for AUX devices


enum IOStatus
{
  nothing = 0,
  byteAvailable = 1,
  atEoF = 2,
  clientLive = 4,
  clientConnected = 8
};
/****************************************************************************************************/
// Class to describe a string buffer, including its length. This saves passing buffer lengths around everywhere.
class StringRef
{
	char *p;		// pointer to the storage
	size_t len;		// number of characters in the storage

public:
	StringRef(char *pp, size_t pl) : p(pp), len(pl) { }

	size_t Length() const { return len; }
	size_t strlen() const;
	char *Pointer() { return p; }
	const char *Pointer() const { return p; }

	char& operator[](size_t index) { return p[index]; }
	char operator[](size_t index) const { return p[index]; }

	void Clear() { p[0] = 0; }

	int printf(const char *fmt, ...);
	int vprintf(const char *fmt, va_list vargs);
	int catf(const char *fmt, ...);
	size_t copy(const char* src);
	size_t cat(const char *src);
};


class FileInfo
{
public:

	bool isDirectory;
	unsigned long size;
	uint8_t day;
	uint8_t month;
	uint16_t year;
	char fileName[FILENAME_LENGTH];
};

class MassStorage
{
public:

  bool FindFirst(const char *directory, FileInfo &file_info);
  bool FindNext(FileInfo &file_info);
  const char* GetMonthName(const uint8_t month);
  const char* CombineName(const char* directory, const char* fileName);
  bool Delete(const char* directory, const char* fileName);
  bool MakeDirectory(const char *parentDir, const char *dirName);
  bool MakeDirectory(const char *directory);
  bool Rename(const char *oldFilename, const char *newFilename);
  bool FileExists(const char *file) const;
  bool PathExists(const char *path) const;
  bool PathExists(const char* directory, const char* subDirectory);

//protected:
  MassStorage(void);//MassStorage(Platform* p);
  bool Init();

private:

  FATFS fileSystem;

  DIR *findDir;

  char combinedNameBuff[FILENAME_LENGTH];
  StringRef combinedName;
};

// This class handles input from, and output to, files.

class FileStore //: public InputOutput
{
public:

	int8_t Status();								// Returns OR of IOStatus
	bool Read(char& b);								// Read 1 byte
	int Read(char* buf, unsigned int nBytes);		// Read a block of nBytes length
	bool Write(char b);								// Write 1 byte
	bool Write(const char *s, unsigned int len);	// Write a block of len bytes
	bool Write(const char* s);						// Write a string
	bool Close();									// Shut the file and tidy up
	unsigned long Position() const;					// Get the current file position
	bool Seek(unsigned long pos);					// Jump to pos in the file
	bool GoToEnd();									// Position the file at the end (so you can write on the end).
	unsigned long Length() const;					// File size in bytes
	float FractionRead() const;						// How far in we are
	void Duplicate();								// Create a second reference to this file
	bool Flush();									// Write remaining buffer data
	static float GetAndClearLongestWriteTime();		// Return the longest time it took to write a block to a file, in milliseconds
  bool inUse;

	FileStore(void);//FileStore(Platform* p);
	void Init();
	bool Open(const char* directory, const char* fileName, bool write);
	bool CreateNew(const char* directory, const char* fileName);

private:
	byte buf[FILE_BUF_LEN];
	unsigned int bufferPointer;
	unsigned long bytesRead;

	bool ReadBuffer();
	bool WriteBuffer();
	bool InternalWriteBlock(const char *s, unsigned int len);

	FIL file;

	bool writing;
	unsigned int lastBufferEntry;
	unsigned int openCount;

	static uint32_t longestWriteTime;
};

// Small class to hold an open file and data relating to it.
// This is designed so that files are never left open and we never duplicate a file reference.
class FileData
{
public:
	FileData() : f(NULL) {}

	// Set this to refer to a newly-opened file
	void Set(FileStore* pfile)
	{
		Close();	// close any existing file
		f = pfile;
	}

	bool IsLive() const { return f != NULL; }

	bool Close()
	{
		if (f != NULL)
		{
			bool ok = f->Close();
			f = NULL;
			return ok;
		}
		return false;
	}

	bool Read(char& b)
	{
		return f->Read(b);
	}

	bool Write(char b)
	{
		return f->Write(b);
	}

	bool Write(const char *s, unsigned int len)
	//pre(len <= 256)
	{
		return f->Write(s, len);
	}

	bool Flush()
	{
		return f->Flush();
	}

	bool Seek(unsigned long position)
	{
		return f->Seek(position);
	}

	float FractionRead() const
	{
		return (f == NULL ? -1.0 : f->FractionRead());
	}

	unsigned long Position() const
	{
		return (f == NULL ? 0 : f->Position());
	}

	unsigned long Length() const
	{
		return f->Length();
	}

	// Assignment operator
	void CopyFrom(const FileData& other)
	{
		Close();
		f = other.f;
		if (f != NULL)
		{
			f->Duplicate();
		}
	}

	// Move operator
	void MoveFrom(FileData& other)
	{
		Close();
		f = other.f;
		other.Init();
	}

private:
	FileStore *f;

	void Init()
	{
		f = NULL;
	}

	// Private assignment operator to prevent us assigning these objects
	FileData& operator=(const FileData&);

	// Private copy constructor to prevent us copying these objects
	FileData(const FileData&);
};

//HSMCI

#ifdef __MACCHINA_M2

static const uint8_t PIN_HSMCI_MCCDA_GPIO = 38;
static const uint8_t PIN_HSMCI_MCCK_GPIO = 37;
static const uint8_t PIN_HSMCI_MCDA0_GPIO = 39;
static const uint8_t PIN_HSMCI_MCDA1_GPIO = 40;
static const uint8_t PIN_HSMCI_MCDA2_GPIO = 41;
static const uint8_t PIN_HSMCI_MCDA3_GPIO = 42;

static const uint8_t PIN_HSMCI_CARD_DETECT_ARDUINO = 36;
static const uint8_t PIN_HSMCI_MCCDA_GPIO_ARDUINO = 38;
static const uint8_t PIN_HSMCI_MCCK_GPIO_ARDUINO = 37;
static const uint8_t PIN_HSMCI_MCDA0_GPIO_ARDUINO = 39;
static const uint8_t PIN_HSMCI_MCDA1_GPIO_ARDUINO = 40;
static const uint8_t PIN_HSMCI_MCDA2_GPIO_ARDUINO = 41;
static const uint8_t PIN_HSMCI_MCDA3_GPIO_ARDUINO = 42;

#else

static const uint8_t PIN_HSMCI_MCCDA_GPIO = 101;
static const uint8_t PIN_HSMCI_MCCK_GPIO = 102;
static const uint8_t PIN_HSMCI_MCDA0_GPIO = 103;
static const uint8_t PIN_HSMCI_MCDA1_GPIO = 104;
static const uint8_t PIN_HSMCI_MCDA2_GPIO = 105;
static const uint8_t PIN_HSMCI_MCDA3_GPIO = 106;

static const uint8_t PIN_HSMCI_CARD_DETECT_ARDUINO = 72;
static const uint8_t PIN_HSMCI_MCCDA_GPIO_ARDUINO = 43;
static const uint8_t PIN_HSMCI_MCCK_GPIO_ARDUINO = 42;
static const uint8_t PIN_HSMCI_MCDA0_GPIO_ARDUINO = 73;
static const uint8_t PIN_HSMCI_MCDA1_GPIO_ARDUINO = 57;
static const uint8_t PIN_HSMCI_MCDA2_GPIO_ARDUINO = 56;
static const uint8_t PIN_HSMCI_MCDA3_GPIO_ARDUINO = 55;

#endif


extern MassStorage SD;


#endif
