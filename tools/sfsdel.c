/*
\file sfsdel.c
\brief this file content the fonction to delete a file in the file system
*/
#include "structure.h"

int strcomp(const char *s1, const char *s2);

/*
This fonction delete a file int the sfs
\param sfs SimpleFileSystem were the files are
\param filename the file to delete
*/
void sfsdel(SimpleFileSystem *sfs, char filename[LENGTH_F]) {
	int fileEntryIndex = 0;

	// Parcours des file entries
	while(strcomp(sfs->fe[fileEntryIndex].name, filename) != 0) {
		fileEntryIndex++;
	}

	// 1er byte du name a 0
	sfs->fe[fileEntryIndex].name[0] = 0;

	// Une fois qu'on a la bonne file entry, boucle sur les Index de blocs et modif du bits correspondant dans bitmap
	int indexInd = 0;
	
	while(sfs->fe[fileEntryIndex].tabIndexes[indexInd] != 0) {

		// printf("TabIndexes[%d] = %d\n", indexInd, sfs->fe[fileEntryIndex].tabIndexes[indexInd]);

		int indexBitmap = sfs->fe[fileEntryIndex].tabIndexes[indexInd]/BIT; //Division entière
		int decalage = sfs->fe[fileEntryIndex].tabIndexes[indexInd]%BIT-1; //-1 parce qu'on decale à partir de la droite
		sfs->bitmap[indexBitmap] &= ~(1<<decalage);
		// printf("Erase in bitmap at index : %d\n", (indexBitmap+decalage));		
		indexInd++;
	} 
}

int strcomp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	    return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}



