/*
*  kernel.c
*/
#include "nomenclature.h"

typedef unsigned char uchar;
	char *str;
void kernel(void) {
	uchar buf[512];
	uchar buf1[512];
	char *str;
	init_syscalls(); 		// ecrase interruption 80 pour la notre
	interrupt(0x80,print_str,"coucou du kernel\0",0,0,0);
	
	interrupt(0x80,write_sect,15,"hello ca va\n",0,0);// Ecrit secteur
	//interrupt(0x80,3,20, buf,0,0); // lit le fichier dans le secteur 20
	//interrupt(0x80,3,15, buf1,0,0); // lit un secteur qu'on vient d'écrire
	interrupt(0x80,iter,20,buf,0,0); // itère sur secteur 20
	while(1){
		interrupt(0x80, read_str,str,0,0,0); // read string
		interrupt(0x80,1,str,0,0,0);
		str = "";
	} // évite d'aller lire plus loin
}

