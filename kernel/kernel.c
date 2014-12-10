/*
*  kernel.c
*/
#include "nomenclature.h"

typedef unsigned char uchar;
	char *str;

void kernel(void) {
	//uchar buf[BlockSize];
	uchar buf1[FESize];
	char *buf;
	char *str;
	int isOk = 0;
	init_syscalls(); 		// ecrase interruption 80 pour la notre
	interrupt(0x80,print_str,"Welcome to OSP3A\0",0,0,0);

	while(isOk == 0)
		interrupt(0x80,iter,isOk,buf,0,0); 
		interrupt(0x80,print_str,buf,0,0,0);
		buf = "";
	}

	while(1){
		interrupt(0x80, read_str,str,0,0,0); // read string
		interrupt(0x80,print_str,str,0,0,0);
		str = "";
	} // évite d'aller lire plus loin
}

