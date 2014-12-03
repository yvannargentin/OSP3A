#ifndef STRUCTURE__
#define STRUCTURE__
#include <stdint.h>


typedef struct __attribute__ ((__packed__)) SuperBlock{
	char signature[8];
	int16_t nbSecteurs;
	int16_t tailleBitmap;
	int16_t tailleFE; //FE = FileEntry
	int16_t blockReservedFE;
	int16_t blockReserverContent;
} SuperBlock;

typedef struct __attribute__ ((__packed__)) FileEntries{
	char name[32];
	int16_t size;
	int16_t tabIndexes[111]; //111 = (tailleFE-name-size)/2
} FileEntries;

typedef struct __attribute__ ((__packed__)) sfs {
	SuperBlock sb;
	char bitmap[1024];
	FileEntries fe[64];
	char fileContent[256][1024];
} SimpleFileSystem;

#endif
