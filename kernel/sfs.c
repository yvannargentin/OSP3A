/*
\file sfs.c
\brief this file content the fonctions for the Simple File System
*/

#include "nomenclature.h"

int Shift = -1;
int counter = 0;
int offset = 1;
// 
/*
This fonction iterate on the files and fill buf
\param isOk = 1 when you reached the end of the FEntries
\param buf that we fill
\return return 0 if succeed
*/
int iterator(int *isOk, char *buf) {
	int nbFE = MaxFe;
	// divide by 2
	char result[BlockSize];
	int i;
	*isOk = 0;

	do{
		counter++;

		if(offset == 0) // switch between first and 2nd FE in the sector
			offset = FESize;
		else{
			offset = 0;
			Shift++;
		}

		if(interrupt(0x80,read_sect,FeStart + Shift, result,0,0) != 0)
			return -1; // error occured in read_sector
		
	}while (&result[offset] == '0');
	if(strcpy(buf,&result[offset],FESize)!= 0)
		return -1; // error occured with strcpy

	if (counter >= nbFE){
		*isOk = 1; // end of FE
		counter = 0;
		Shift = -1;
	}
	
	
	return 0;
}



/*
This fonction get the stats of the file and put it on a structure
\param filename the name of the file to read
\param stat_st *stat the structure that we fill
\return return 0 if succeed and -1 if failure
*/
int get_stat(char *filename, struct stat_st *stat) {
	
	char buf[FESize];
	int offset_size = OffsetSize; // 32	
	int tmp;
	int tmp2;
	int size;

	int length_str;	
	int *isOk = 0;
	char str[6]; //2**16 => 5 chars, slot for \0
	int result= 0;
	do {
		if(iterator(&isOk, buf) != 0)
			return -1; // error occured in iterator
	} while ((strcomp(&buf, filename) != 0) && (isOk == 0));

	//If the file doesnt exist
	if(isOk == 1){
		//interrupt(0x80,print_str,"File not found",0,0,0);
		if(print_string("File not found")!= 0)
			return -1; // error occured in print_string
		return -1;
	}

	tmp = buf[offset_size++];
	tmp2 = buf[offset_size];
	size = tmp+(tmp2<<8);
	
	//Copy filename in structure
	strncpy(stat->filename, filename, 32);
	stat->size = size;
	
	length_str = lengthInt(size);
	
	intTostr(str, size, length_str);

	if(interrupt(0x80,print_str,stat->filename,0,0,0)!= 0)
		return -1; // error occured in print_string
	if(interrupt(0x80,print_str,str,0,0,0)!= 0)
		return -1; // error occured in print_string

	
	while(isOk == 0) // we still want to reset the iterator so we keep iterating till isOk == 1
		if(iterator(&isOk, buf) != 0)
			return -1; // error occured in iterator

	return 0;
}

/*
This fonction removes a file which name's given in parameter
\param filename the name of the file to remove
\return return 0 if succeed and -1 if failure
*/
int remove_file(char *filename) {	
	// Iterate on fileEntries
	uchar buf[BlockSize];
	unsigned int noSector = FeStart;	// Sector number containing fe (24 for the first one)
	unsigned int offset = 0;		// offset of fe in sector (0 or 256)
	unsigned int counter = 0;
	unsigned char map[BlockSize];
	unsigned int debutIndexes = TabIndexesStart;
	unsigned int indexFile;
	unsigned int indexBitmap;
	unsigned int decalage;
	unsigned int indexF;
	unsigned int tmp;
	unsigned int tmp2;

	// Find 
	do {
		if(interrupt(0x80,read_sect,noSector, buf,0,0)!= 0)
			return -1; // error occured in read_sector
		// Inc counter each 2 fe (one sector contains 2 fe)
		if((counter%2) == 1)
			noSector++;
		// Offset is 0 or 256 (BlockSize/2). fe is either at the begining of the sector or just at the middle (2fe for each sectors)
		if(offset == 0)
			offset = FESize;
		else
			offset = 0;
		counter++; 
		
	} while (strcomp(&buf[offset],filename) != 0 || counter > 64);
	
	if(counter > 64)
		return -1;	// File not found

	// byte 0 of name = 0
	buf[offset] = 0;

	// Load bitmap
	if(interrupt(0x80, read_sect, BtmStart, map, 0, 0) != 0)
		return -1; // error occured in read_sector

	// Get the offset of the first file index
	indexFile = offset+debutIndexes;

	// Iterate on fileIndexes
	do {
		// Retreives the int value of file index
		tmp = buf[indexFile++];
		tmp2 = buf[indexFile++];
		indexF = tmp+(tmp2<<8);

		// Find the bit to change in the bitmap
		indexBitmap = indexF/8;
		decalage = (indexF%8)-1;
		// Put the bit to 0
		map[indexBitmap] &= ~(1<<decalage);
	} while(indexF != 0);

	// Saving bitmap to image
	if(interrupt(0x80, write_sect, BtmStart, map, 0, 0)!= 0)
		return -1; // error occured in write_sector
	// Saving file entry sector
	if(interrupt(0x80, write_sect, noSector-1, buf, 0, 0)!= 0)
		return -1; // error occured in write_sector

	if(interrupt(0x80, print_str, "File deleted", 0, 0, 0) != 0)
		return -1; // error occured with print_string

	return 0;
}

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
		if(interrupt(0x80,read_sect,nb_sector_fe, sect,0,0) != 0)
			return -1; //error occured in read_sector

		if(modulo(cpt,2) == 1)
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
		tmp = sect[indexes++];
		tmp2 = sect[indexes++];
		index = tmp+(tmp2<<8);
		nb_sector_fc = FCStart + index;	
		
		// read the content of fileContent 
		if(interrupt(0x80,read_sect,nb_sector_fc, content,0,0) != 0)
			return -1; // error occured in read_sector
		strncpy(buf,&content, BlockSize); // copy the content in the buffer
		
		// content separted in 2 sectors
		if (lengthStr(content) == BlockSize){
			if(interrupt(0x80,read_sect,nb_sector_fc+1, content,0,0) != 0)
				return -1; // error occured in read_sector
			strncpy(buf, &content, BlockSize); // copy the content in the buffer
		}

	} while (index != 0);
	// interrupt(0x80,print_str, "file readed", 0, 0,0);
	return 0;	
}

