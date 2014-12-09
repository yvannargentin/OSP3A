extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
extern int modulo(int a, int b);
#include "nomenclature.h"
typedef unsigned char uchar;

int remove_file(char *filename) {
	
	// Iterate on fileEntries
	uchar buf[BlockSize];
	int noSector = FeStart;	// Sector number containing fe (24 for the first one)
	int offset = 0;		// offset of fe in sector (0 or 256)
	int compteur = 0;
	unsigned char map[BlockSize];
	int debutIndexes = 34;
	int indexFile;
	int indexBitmap;
	int decalage;
	int indexF;

	do {
		interrupt(0x80,read_sect,noSector, buf,0,0);
		// interrupt(0x80,print_str,buf,0,0,0); 

		if((compteur%2) == 1)
			noSector++;
		
		if(offset == 0)
			offset = BlockSize/2;
		else
			offset = 0;

		compteur++; 
		
	} while (strcomp(&buf[offset],filename) != 0 || compteur > 64);
	
	if(compteur > 64)
		return -1;	// File not found

	interrupt(0x80,print_str,buf,0,0,0); 

	// byte 0 of name = 0
	buf[offset] = 0;
	interrupt(0x80,print_str,"First name byte changed to 0",0,0,0); 

	// Load bitmap
	interrupt(0x80, read_sect, BtmStart, map, 0, 0);
	interrupt(0x80,print_str,"Loading bitmap from sect 22",0,0,0); 


	indexFile = offset+34;
	// Getting int value from file index
	indexF = /*Magic code*/0;

	// Iterate on fileIndexes
	while (indexF != 0) {
		indexF = &buf[indexFile] - 0;
		interrupt(0x80,print_str,"Iterating...",0,0,0); 
		interrupt(0x80,print_str,&buf[indexFile],0,0,0); 

		indexBitmap = buf[indexFile]/8;
		decalage = indexF%8-1;

		map[indexBitmap] &= ~(1<<decalage);
		indexFile += 2;

		
	}

	// Saving bitmap to image
	interrupt(0x80, write_sect, BtmStart, map, 0, 0);
	interrupt(0x80,print_str,"Bitmap saved",0,0,0); 
	// Saving file entry sector
	interrupt(0x80, write_sect, noSector, buf, 0, 0); 
	interrupt(0x80,print_str,"File entry saved",0,0,0); 
	interrupt(0x80,print_str,"End remove",0,0,0); 

	return 0;
}

