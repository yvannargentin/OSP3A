/*
\file sfsadd.c
\brief this file content the fonction to add a file in the file system
*/
#ifndef STRUCTURE__
#define STRUCTURE__
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_CONTENT 1024
#define BLOCK 256
#define LENGTH_F 32
#define BIT 8
#define MAX_FE 64
#define MAX_INDEX 111 //111 = (tailleFE-name-size)/2
#define LENGTH_SB 18
#define ReservedFE 16

/* structure who contain the SuperBlock
\struct SuperBlock
*/
typedef struct __attribute__ ((__packed__)) SuperBlock{
	char signature[BIT];
	int16_t nbSecteurs;
	int16_t tailleBitmap;
	int16_t tailleFE; //FE = FileEntry
	int16_t blockReservedFE;
	int16_t blockReserverContent;
} SuperBlock;

/* structure who contain the FileEntries
\struct FileEntries
*/
typedef struct __attribute__ ((__packed__)) FileEntries{
	char name[LENGTH_F ];
	int16_t size;
	int16_t tabIndexes[MAX_INDEX]; 
} FileEntries;

/* structure who contain the Simple File System
\struct sfs
*/
typedef struct __attribute__ ((__packed__)) sfs {
	SuperBlock sb;
	char bitmap[MAX_CONTENT];
	FileEntries fe[MAX_FE];
	char fileContent[BLOCK][MAX_CONTENT];
} SimpleFileSystem;


#endif
