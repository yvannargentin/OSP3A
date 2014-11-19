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


void sfsdel(sfs x, char* file) {
	char fileToDelete[32] = file;
	
	int fileEntryIndex = 0;
		
	// Parcours des file entries	
	while(sfs.fe[fileEntryIndex].Name != fileToDelete) {
		fileEntryIndex++;
	}

	// 1er bit du name a 0
	sfs.fe[fileEntryIndex].Name &= ~(1<<0);


	FileEntries entry = sfs.fe[fileEntryIndex];
	// Une fois qu'on a la bonne file entry, boucle sur les Index de blocs et modif du bits correspondant dans bitmap
	int indexInd = 0;
	while(entry.tabIndexes[indexInd] != 0) {
		sfs.bitmap &= ~(1<<entry.tabIndexes[indexInd]);
		indexInd++;
	}
}




