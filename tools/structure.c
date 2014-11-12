#include <string.h>
#include <stdio.h>

typedef struct SuperBlock{
	char signature[8];
	int nbSecteurs;
	int tailleBitmap;
	int tailleFE; //FE = FileEntry
	int blockReservedFE;
	int blockReserverContent;
} SuperBlock;

typedef struct FileEntries{
	char name[32];
	int size;
	int tabIndexes[111]; //111 = (tailleFE-name-size)/2
} FileEntries;

typedef struct sfs {
	SuperBlock sb;
	char bitmap[1024];
	FileEntries fe;
	char fileContent[256][1024];
} SimpleFileSystem;

int main (int argc, char *argv){
	SimpleFileSystem sfs;
	strcpy(sfs.sb.signature, "SFSv0100");
	sfs.sb.nbSecteurs = 2;
	sfs.sb.tailleBitmap = 1;
	sfs.sb.tailleFE = 256;
	sfs.sb.blockReservedFE = 16;
	sfs.sb.blockReserverContent = 256;

	//Remplir bitmap que avec des 0
	int i;
	for(i=0; i<sizeof(sfs.bitmap); i++){
		sfs.bitmap[i] = '0';
	}
}
