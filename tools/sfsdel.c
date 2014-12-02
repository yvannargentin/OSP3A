#include "structure.h"

int strcomp(const char *s1, const char *s2);

void sfsdel(SimpleFileSystem *sfs, char filename[32]) {
	printf("Welcome in sfsdel\n");
	int fileEntryIndex = 0;

	// Parcours des file entries
	
	//printf("filename %s, fileentry %s, %d \n", filename, sfs->fe[fileEntryIndex].name, (filename == sfs->fe[fileEntryIndex].name));

	while(strcomp(sfs->fe[fileEntryIndex].name, filename) != 0) {
		fileEntryIndex++;
	}

	printf("fileEntryIndex : %d\n", fileEntryIndex);

	// 1er byte du name a 0
	sfs->fe[fileEntryIndex].name[0] = 0;

	// Une fois qu'on a la bonne file entry, boucle sur les Index de blocs et modif du bits correspondant dans bitmap
	int indexInd = 0;
	
	while(sfs->fe[fileEntryIndex].tabIndexes[indexInd] != 0) {

		printf("TabIndexes[%d] = %d\n", indexInd, sfs->fe[fileEntryIndex].tabIndexes[indexInd]);

		int indexBitmap = sfs->fe[fileEntryIndex].tabIndexes[indexInd]/8; //Division entière
		int decalage = sfs->fe[fileEntryIndex].tabIndexes[indexInd]%8-1; //-1 parce qu'on decale à partir de la droite
		sfs->bitmap[indexBitmap] &= ~(1<<decalage);
		printf("Erase in bitmap at index : %d\n", (indexBitmap+decalage));		
		indexInd++;
	} 

	printf("End of sfsdel\n");
}

int strcomp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	    return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

