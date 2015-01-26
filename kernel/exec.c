/*
\file exec.c
\brief this file content the exec fonction
*/
#include "nomenclature.h"

int execute(char *filename, uint seg){
	unsigned char *contenu;
	int i;

        //load binary image in memory (adress X)
	if (read_file(filename, contenu) != 0)  // read the content of the file
		print_string("erreur read_file");
	else{

		//print_string(contenu);
		if (lengthStr(contenu) == 0)
			return 1;
		else {
			for(i=0; i<lengthStr(contenu); i++){
				memputb(seg, 0, contenu[i]); // copy image from X in seg
				
			}
			jump(seg); // jump to seg
			
			return 0;
		}
	}
}
