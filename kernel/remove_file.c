extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
typedef unsigned char uchar;

int remove_file(char *filename) {
	
	// Iterate on fileEntries
	uchar buf[512];
	int noSector = 24;	// Sector number containing fe (24 for the first one)
	int offset = 0;		// offset of fe in sector (0 or 256)
	int compteur = 0;

	do {		
		interrupt(0x80, read_sect, noSector, buf, 0, 0);

		if((compteur%2) == 1)
			noSector++;
		if(offset == 0)
			offset = 256;
		else
			offset = 0;

		compteur++;
	} while(strcomp(buf[offset], filename));

	// byte 0 of name = 0
	buf[offset] = 0;

	// Load bitmap
	uchar map[512];
	interrupt(0x80, read_sect, 22, map, 0, 0);


	int indexFile = offset+34;

	// Iterate on fileIndexes
	while (buf[indexFile] != 0) {
		int indexBitmap = buf[indexFile]/8;
		int decalage = buf[indexFile]%8-1;

		map[indexBitmap] &= ~(1<<decalage);
		indexFile += 2;
	}

	// Saving bitmap to image
	interrupt(0x80, write_sect, 22, map, 0, 0);
	// Saving file entry sector
	interrupt(0x80, write_sect, noSect, buf, 0, 0);
}

