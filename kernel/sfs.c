extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
#include "nomenclature.h"

typedef unsigned char uchar;


int floor(int val,int diviseur);

void iterator(int compteur) {
	// divise par 2
	int decalage = floor(compteur, 2);
	
	uchar buf[tailleFE*2];  // *2 car 1 FE = 1/2 secteur
	interrupt(0x80,read_sect,debutFe + decalage, buf,0,0);
	
}

int get_stat(char *filename, struct stat_st *stat) {
}

int read_file(char *filename, unsigned char *buf) {
}

int remove_file(char *filename) {
}

int floor(int val,int diviseur){
	int resultat = 0;
	while(val % diviseur != 0)
		val -= 1; 
	resultat = val / diviseur;
	return resultat;
}


