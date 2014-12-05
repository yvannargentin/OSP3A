int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;

// le sfs est écris au secteur 20 le Superblock prend 2 secteur
// le bitmap prends 2 secteurs donc on commence le FileEntrie à 24

#define tailleFileEntry 256
int decalage = 0;
void iterator() {
	uchar buf[tailleFileEntry]; 
	interrupt(0x80,read_sect,StartFileEntries + decalage, buf,0,0);
	
}

int get_stat(char *filename, struct stat_st *stat) {
}

int read_file(char *filename, unsigned char *buf) {
}

int remove_file(char *filename) {
}

