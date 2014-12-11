/*
*  kernel.c
*/
#include "nomenclature.h"

typedef unsigned char uchar;

void kernel(void) {
	//uchar buf[BlockSize];
	uchar buf1[FESize];
	char buf[FESize];
	char *str;
	int isOk = 0;
	int counter = 0;
	init_syscalls(); 		// ecrase interruption 80 pour la notre
	interrupt(0x80,print_str,"Welcome to OSP3A\0",0,0,0);

	while(isOk == 0 & counter < 10){
		interrupt(0x80,iter,isOk,buf,0,0); 
		interrupt(0x80,print_str,buf,0,0,0);
		counter++;
	}

	while(1){
		interrupt(0x80, read_str,str,0,0,0); // read string
		interrupt(0x80,print_str,str,0,0,0);
	} // évite d'aller lire plus loin

}

