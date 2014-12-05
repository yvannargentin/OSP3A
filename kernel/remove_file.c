

int remove_file(char *filename) {
	
	// Iterate on files with iterator

	FileEntry *entry;
	do {
		entry = iterator.next();	// When found get the corresponding file entry
	} while(strcomp(entry->name, filename) != 0);

	// Put 0 at the first byte of name
	entry->name[0] = 0;

	// Go through file indexes, put 0 at corresponding bit in bitmap
	int indexInd = 0;

	// Load bitmap
	// TO DO
	
	
	while(entry->tabIndexes[indexInd] != 0) {

		int indexBitmap = entry->tabIndexes[indexInd]/8; //Division entière
		int decalage = entry->tabIndexes[indexInd]%8-1;	 //-1 parce qu'on decale à partir de la droite
		sfs->bitmap[indexBitmap] &= ~(1<<decalage);
	
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
