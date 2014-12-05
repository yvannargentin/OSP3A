int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;
void iterator() {
	uchar buf[512];
	// le sfs est écris au secteur 20
	interrupt(0x80,read_sect,24, buf,0,0);
	
}

int get_stat(char *filename, struct stat_st *stat) {
}

int read_file(char *filename, unsigned char *buf) {
}

int remove_file(char *filename) {
}
