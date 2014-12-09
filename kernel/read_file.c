#include "nomenclature.h"
extern int strcomp(const char *s1, const char *s2);

int read_file(char *filename, unsigned char *buf){
	int nb_sector_fe = FeStart;
	int offset = 0;
	unsigned char sect[BlockSize];
	int cpt = 0;
	int index;
	int indexes = TabIndexesStart;
	int nb_sector_fc = 0;
	unsigned char contenu[BlockSize];

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
	index = 1 ; //&sect[indexes];

	// iterate on the tabIndexes used
	//while (index != 0){

		nb_sector_fc = FCStart + index;	
		
		//print_string("iterating on the tabindexes");
		
		// read the content of fileContent 
		interrupt(0x80,read_sect,nb_sector_fc, contenu,0,0); 
		// content separted in 2 sectors
		if (length(contenu) == BlockSize -1)
			interrupt(0x80,read_sect,nb_sector_fc+1, contenu,0,0);
		interrupt(0x80,print_str, contenu, 0, 0,0);
		nb_sector_fc += 2; // jump to the next fileContent
		index++;	//jump to the next tabIndexes
	//}
	
	return 0;	
}

// get the length of a table of char
int length(char* tab){
	int i = 0;
	while(tab[i] !='\0'){		
		i += 1;
	}
	return i;
}

