#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	int tailleBitmap = sfs.sb.tailleBitmap*1024;
	for(i=0; i<tailleBitmap; i++){
		sfs.bitmap[i] = 0;
	}
	return sfs;
}
<<<<<<< HEAD:tools/structure.c

int main(int argc, char **argv){
	SimpleFileSystem sf = sfscreate("sfs");
	sfsadd(sf, "test.txt");
	//sfsls(sf);
	//sfsdel(sf, "test.txt");
}
=======
>>>>>>> 55368f7e0c40feebbb7d3434c089475d352736d0:tools/sfscreate.c
