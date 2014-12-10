#include "nomenclature.h"
// #include "structure.h"

extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

typedef unsigned char uchar;


int strcomp(const char *s1, const char *s2);
int Shift = 0;
int counter = 0;
int offset = 0;
// fill buf with F, isOk indicates if you can keep calling iterator or not
int iterator(int isOk, char *buf) {
	// divide by 2

	while(buf[offset] == '0'){

		if(offset == 0) // switch between first and 2nd FE in the sector
			offset = FESize;
		else{
			offset = 0;
			Shift++;
		}

		interrupt(0x80,read_sect,FeStart + Shift, buf,0,0);
		counter++;	
	}
	isOk = 0;
	if (counter >= 64)
		isOk = 1; // end of FE

	return 0;
}

int get_stat(char *filename, struct stat_st *stat) {
}


int strcomp(char *s1, char *s2) {
	for ( ; *s1 == *s2; s1++, s2++){
		if (*s1 == '\0')
		    return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


