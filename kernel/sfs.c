extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;


int divfloor(int val,int divisor);
int strcomp(const char *s1, const char *s2);

int iterator(int counter, char *buf) {
	// divide by 2
	int Shift = divfloor(counter, 2);
	interrupt(0x80,read_sect,FeStart + Shift, buf,0,0);
	return 0;
}

int get_stat(char *filename, struct stat_st *stat) {
}

int divfloor(int val,int divisor){
	int result = 0;
	while(modulo(val, divisor) != 0)
		val -= 1; 
	
	result = val / divisor;
	
	return result;
}


int strcomp(char *s1, char *s2) {
	for ( ; *s1 == *s2; s1++, s2++){
		if (*s1 == '\0')
		    return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


