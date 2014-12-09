extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
extern int modulo(int a, int b);
#include "nomenclature.h"
typedef unsigned char uchar;


/* remove_file.c
 * Removes a file which name's given in parameter
 */
int remove_file(char *filename) {
	
	// Iterate on fileEntries
	uchar buf[BlockSize];
	int noSector = FeStart;	// Sector number containing fe (24 for the first one)
	int offset = 0;		// offset of fe in sector (0 or 256)
	int counter = 0;
	unsigned char map[BlockSize];
	int debutIndexes = 34;
	int indexFile;
	int indexBitmap;
	int decalage;
	int indexF;
	int tmp;
	int tmp2;

	// Find 
	do {
		interrupt(0x80,read_sect,noSector, buf,0,0);
		// Inc counter each 2 fe (one sector contains 2 fe)
		if((counter%2) == 1)
			noSector++;
		// Offset is 0 or 256 (BlockSize/2). fe is either at the begining of the sector or just at the middle (2fe for each sectors)
		if(offset == 0)
			offset = BlockSize/2;
		else
			offset = 0;
		counter++; 
		
	} while (strcomp(&buf[offset],filename) != 0 || counter > 64);
	
	if(counter > 64)
		return -1;	// File not found

	// byte 0 of name = 0
	buf[offset] = 0;
	interrupt(0x80,print_str,"First name byte changed to 0",0,0,0); 

	// Load bitmap
	interrupt(0x80, read_sect, BtmStart, map, 0, 0);
	interrupt(0x80,print_str,"Loading bitmap from sect 22",0,0,0); 

	// Get the offset of the first file index
	indexFile = offset+debutIndexes;

	// Iterate on fileIndexes
	do {
		// Retreives the int value of file index
		tmp = buf[indexFile++];
		tmp2 = buf[indexFile++];
		indexF = tmp+tmp2<<8;

		interrupt(0x80,print_str,"Iterating...",0,0,0); 

		// Find the bit to change in the bitmap
		indexBitmap = indexF/8;
		decalage = indexF%8-1;
		// Put the bit to 0
		map[indexBitmap] &= ~(1<<decalage);
	} while(indexF != 0);

	// Saving bitmap to image
	interrupt(0x80, write_sect, BtmStart, map, 0, 0);
	interrupt(0x80,print_str,"Bitmap saved",0,0,0);  
	// Saving file entry sector
	interrupt(0x80, write_sect, noSector-1, buf, 0, 0); 
	interrupt(0x80,print_str,"File entry saved",0,0,0);

	return 0;
}

