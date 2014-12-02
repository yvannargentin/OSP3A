#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
 

void sfsls(SimpleFileSystem monSFS) {
	int nbFiles = 0;
	bool continuer = true;
	printf(" - Nom - Taille -\r\n");
	while(continuer){
		if(nbFiles >= monSFS.sb.tailleFE - 1   || monSFS.fe[nbFiles].size == 0)
			continuer = false;
		if(continuer){
			if(monSFS.fe[nbFiles].name[0] != 0){
				printf(" - %s - %d -\r\n",monSFS.fe[nbFiles].name,monSFS.fe[nbFiles].size);
			}
				nbFiles++;
		}
	}

}
