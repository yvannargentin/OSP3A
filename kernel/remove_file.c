extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
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

	do {
		
		interrupt(0x80,read_sect,noSector, buf,0,0); // lit un secteur qu'on vient d'écrire 
		
		if(modulo(compteur,2) == 1)
			noSector++;
		if(offset == 0)
			offset = BlockSize/2;
		else
			offset = 0;

		compteur++;

		
	} while (strcomp(buf[offset],filename));

	// byte 0 of name = 0
	buf[offset] = 0;

	// Load bitmap
	interrupt(0x80, read_sect, BtmStart, map, 0, 0);


	indexFile = offset+34;

	// Iterate on fileIndexes
	while (buf[indexFile] != 0) {
		int indexBitmap = buf[indexFile]/8;
		int decalage = modulo(buf[indexFile],8-1);

		map[indexBitmap] &= ~(1<<decalage);
		indexFile += 2;
	}

	// Saving bitmap to image
	interrupt(0x80, write_sect, BtmStart, map, 0, 0);
	// Saving file entry sector
	interrupt(0x80, write_sect,noSector, buf, 0, 0);
}

