#include <string.h>
#include <stdio.h>
#include "structure.h"


void sfsdel(SimpleFileSystem sfs, char file[32]) {
	//char fileToDelete[32] = file;
	
	int fileEntryIndex = 0;
		
	// Parcours des file entries	
	while(sfs.fe[fileEntryIndex].name != file) {
		fileEntryIndex++;
	}

	// 1er bit du name a 0
	sfs.fe[fileEntryIndex].name[0] = 0;


	FileEntries entry = sfs.fe[fileEntryIndex];
	// Une fois qu'on a la bonne file entry, boucle sur les Index de blocs et modif du bits correspondant dans bitmap
	int indexInd = 0;
	while(entry.tabIndexes[indexInd] != 0) {
		int indexBitmap = entry.tabIndexes[indexInd]/8;
		sfs.bitmap[indexBitmap] &= ~(1<<8-entry.tabIndexes[indexInd]);
		indexInd++;
	}
}




