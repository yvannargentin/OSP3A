extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;


int divfloor(int val,int divisor);
int modulo(int val, int divisor); // temporary

int iterator(int counter, char *buf) {
	// divide by 2
	int Shift = divfloor(counter, 2);
	interrupt(0x80,read_sect,FeStart + Shift, buf,0,0);
	return 0;
}

int get_stat(char *filename, struct stat_st *stat) {
}

int read_file(char *filename, unsigned char *buf) {
}

int remove_file(char *filename) {
}

int divfloor(int val,int divisor){
	int result = 0;/*
	while(modulo(val, divisor) != 0)
		val -= 1; 
	*/
	result = val / divisor;
	
	return result;
}

