extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;

int get_stats(char *filename) {
	
	uchar buf[BlockSize/2];
	int offset_size = 32;	

	do {
		buf = FonctionDeYvann();
	} while (strcomp(buf, filename) != 0);

	interrupt(0x80,print_str,buf[offset_size],0,0,0);
}
