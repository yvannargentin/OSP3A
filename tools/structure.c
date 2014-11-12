#include <string.h>
#include <stdio.h>
#include "structure.h"

SimpleFileSystem sfscreate (char *sfsName){
	SimpleFileSystem sfs;
	strcpy(sfs.sb.signature, "SFSv0100");
	sfs.sb.nbSecteurs = 2;
	sfs.sb.tailleBitmap = 1;
	sfs.sb.tailleFE = 256;
	sfs.sb.blockReservedFE = 16;
	sfs.sb.blockReserverContent = 256;

	//Remplir bitmap que avec des 0
	int i;
	int tailleBitmap = sfs.sb.tailleBitmap*1024
	for(i=0; i<tailleBitmap; i++){
		sfs.bitmap[i] = '0';
	}
}

int main(int argc, char **argv){
//
}
