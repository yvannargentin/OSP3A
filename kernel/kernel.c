/*
\file sfs.c
\brief this file content the fonctions for the Simple File System
*/

#include "nomenclature.h"

/*
This fonction get the stats of the file and put it on a structure
\param filename the name of the file to read
\param stat_st *stat the structure that we fill
\return return 0 if succeed and -1 if failure
*/

// used for the tests of the different fonctions
void iterate();

int *isOk = 0;
char buf[FESize];
void kernel(void) {
	uchar buf1[BlockSize];
	uchar buf2[BlockSize];
	char *str;
	stat_st stats;

	init_syscalls(); 		// ecrase interruption 80 pour la notre
	// print string

	interrupt(0x80,print_str,"Welcome to OSP3A\0",0,0,0);
	//interrupt(0x80,print_str,"Decommentez votre code dans le kernel pour tester\0",0,0,0);

	/*
	 // write and read sector
	if(interrupt(0x80, write_sect,10,"Ecriture  dans secteur 10",0,0)!= 0)
		interrupt(0x80,print_str,"erreur write_sector",0,0,0);
	if(interrupt(0x80, read_sect,10,buf2,0,0)!= 0)
		interrupt(0x80,print_str,"erreur read_sector",0,0,0);
	if(interrupt(0x80,print_str,buf2,0,0,0)!= 0)
		interrupt(0x80,print_str,"erreur print_string",0,0,0);
	*/
	
	interrupt(0x80, print_str, "========== Test de iterator ==========", 0, 0, 0);

	// display what's in the FEs
	iterate();
	
	//get stat 
	interrupt(0x80, print_str, "========== Test de get_stats ==========", 0, 0, 0);
	
	if(interrupt(0x80, get_st,"test.txt",&stats,0,0) != 0)
		interrupt(0x80,print_str,"erreur get_stat",0,0,0);
	
	
	interrupt(0x80, print_str, "========== Test de read file ==========", 0, 0, 0);
	 // read file
	if(interrupt(0x80, read_f,"fichier.txt",buf1,0,0) != 0){
		interrupt(0x80,print_str,"erreur read_file",0,0,0);
	}else
		interrupt(0x80,print_str,&buf1,0,0,0); 

	
	interrupt(0x80, print_str, "========== Test de remove file ==========", 0, 0, 0);
	
	// display what's in the FEs
	iterate();

	 // remove file
	if(interrupt(0x80, remove_f,"fichier.txt",0,0,0)!= 0)
		interrupt(0x80,print_str,"erreur remove_file",0,0,0);
	
	 // display what's in the FEs
	iterate();

	// read string
	while(1){
		interrupt(0x80, read_str,str,0,0,0); // read string
		interrupt(0x80,print_str,str,0,0,0);
	} // évite d'aller lire plus loin

}
void iterate(){
	isOk = 0;
	while(isOk == 0){
		if(interrupt(0x80,iter,&isOk,buf,0,0) != 0){
			interrupt(0x80,print_str,"erreur iterator",0,0,0);
		}else
			if(strcomp(buf,"") != 0)// we don't weant to display empty FE
				interrupt(0x80,print_str,buf,0,0,0);
	} 
}

