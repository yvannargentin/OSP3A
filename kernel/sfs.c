extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;


int floor(int val,int diviseur);

void iterator(int compteur) {
	// divide by 2
	int decalage = floor(compteur, 2);
	
	uchar buf[BlockSize];  // *2 because 1 FE = 1/2 sector
	interrupt(0x80,read_sect,FeStart + decalage, buf,0,0);
	
}

int get_stat(char *filename, struct stat_st *stat) {
}

int read_file(char *filename, unsigned char *buf) {
}

int remove_file(char *filename) {
}

int floor(int val,int divisor){
	int result = 0;
	while(modulo(val, divisor) != 0)
		val -= 1; 
	result = val / divisor;
	return result;
}

int modulo(int val, int divisor){
	int result = 0;
	 
}

