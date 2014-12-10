/*
\file read_file.c
\brief this file content the fonctions to read a file 
*/

#include "nomenclature.h"
extern int strcomp(const char *s1, const char *s2);
char* strncpy(char *s1, const char *s2, size_t n);
int length(char* tab);

/*
This fonction read the content of the file in param and fill a buffer with it
\param filename the name of the file to read
\param buf the content of the file
\return return 0 if succeed and -1 if failure
*/
int read_file(char *filename, unsigned char *buf){
	int nb_sector_fe = FeStart;
	int offset = 0;
	unsigned char sect[BlockSize];
	int cpt = 0;
	int index;
	int indexes = TabIndexesStart;
	int nb_sector_fc = 0;
	unsigned char content[BlockSize];
	int tmp;
	int tmp2;

	//get the right sector number and the buffer of this sector
	//a sector as 2 FileEntries
	do {
		interrupt(0x80,read_sect,nb_sector_fe, sect,0,0); 

		if(cpt%2 == 1)
			nb_sector_fe++;

		// offset is to know which FileEntry we are going to use in this sector
		if(offset == 0)
			offset = BlockSize/2; 
		else
			offset = 0;

		// exit if the file is note found
		if (cpt > MaxFe)
			return -1;

		cpt++;
	} while (strcomp(&sect[offset],filename) != 0);

	indexes += offset; // get where the tabIndexes starts

	// iterate on the tabIndexes used
	do {
		// get the value of the tabIndexes
		tmp = buf[indexes++];
		tmp2 = buf[indexes++];
		index = tmp+(tmp2<<8);
		nb_sector_fc = FCStart + index;	
		
		// read the content of fileContent 
		interrupt(0x80,read_sect,nb_sector_fc, content,0,0);
		//interrupt(0x80,print_str, content, 0, 0,0);
		
		//interrupt(0x80,print_str, "content in buf", 0, 0,0);
		strncpy(buf, content, length(content)); // copy the content in the buffer
		
	//	interrupt(0x80,print_str, "rest of content", 0, 0,0);
		
		// content separted in 2 sectors
		if (length(content) == BlockSize -1){
			interrupt(0x80,read_sect,nb_sector_fc+1, content,0,0);
			strncpy(buf, content, BlockSize); // copy the content in the buffer
		}
		interrupt(0x80,print_str, buf, 0, 0,0);
	} while (index != 0);
		

	interrupt(0x80,print_str, "file readed", 0, 0,0);

	interrupt(0x80,print_str, buf, 0, 0,0);
	return 0;	
}

char* strncpy(char *s1, char *s2, int n){
    char *s = s1;
    while (n > 0 && *s2 != '\0') {
	*s++ = *s2++;
	--n;
    }
    while (n > 0) {
	*s++ = '\0';
	--n;
    }
    return s1;
}


/*
This fonction get the length of a string
\param tab the content of the file
\return return the length
*/
int length(char* tab){
	int i = 0;
	while(tab[i] !='\0')		
		i += 1;
	
	return i;
}

