/*
\file sfscreate.c
\brief this file content the fonction to add a file in the file system
*/
#include "structure.h"

/*
This fonction create a sfs
\param sfsName name of the sfs
\return return the sys 
*/
SimpleFileSystem sfscreate (char *sfsName){
	SimpleFileSystem sfs;
	strcpy(sfs.sb.signature, "SFSv0100");
	sfs.sb.nbSecteurs = 2;
	sfs.sb.tailleBitmap = 1;
	sfs.sb.tailleFE = BLOCK;
	sfs.sb.blockReservedFE = ReservedFE;
	sfs.sb.blockReserverContent = BLOCK;

	//Fill the bitmap with 0
	int i;
	int tailleBitmap = sfs.sb.tailleBitmap*MAX_CONTENT;
	for(i=0; i<tailleBitmap; i++){
		sfs.bitmap[i] = 0;
	}
	return sfs;
}

