#include <string.h>
#include <stdio.h>
#include "structure.h"


void sfsdel(SimpleFileSystem *sfs, char filename[32]) {
	printf("Welcome in sfsdel");
	int fileEntryIndex = 0;
		
	// Parcours des file entries	
	while(sfs->fe[fileEntryIndex].name != filename) {
		fileEntryIndex++;
	}

	printf("fileEntryIndex : %d", fileEntryIndex);

	// 1er byte du name a 0
	sfs->fe[fileEntryIndex].name[0] = 0;


	// FileEntries *entry = sfs->fe[fileEntryIndex];
	// Une fois qu'on a la bonne file entry, boucle sur les Index de blocs et modif du bits correspondant dans bitmap
	int indexInd = 0;
	while(sfs->fe[fileEntryIndex].tabIndexes[indexInd] != 0) {
		int indexBitmap = sfs->fe[fileEntryIndex].tabIndexes[indexInd]/8; //Division entière
		int decalage = sfs->fe[fileEntryIndex].tabIndexes[indexInd]%8-1; //-1 parce qu'on decale à partir de la droite
		sfs->bitmap[indexBitmap] &= ~(1<<decalage);
		indexInd++;
	}
}



