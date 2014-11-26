#include <string.h>
#include <stdio.h>


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




