#include <stdio.h>
#include <stdlib.h>


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
} sfs;

int main(int argc, char** argv) {
	// Création du sfs
	sfs x = {};

	char toDelete[32] = "aFile";
	// Appel a la fonction
	sfsdel(x, toDelete);	

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




