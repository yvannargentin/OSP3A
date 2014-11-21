#include <string.h>
#include <stdio.h>
#include <structure.h>
 

int ls(sfs monSFS) {
	int nbFiles = 0;
	bool continuer = true;
	printf(" - Nom - Taille -\r\n");
	while(continuer){
		printf(" - %s - %d -\r\n",monSFS.fe[nbFiles].name,monSFS.fe[nbFiles].size);
		nbFiles++;
		if(nbFiles >= monSFS.sb.tailleFE - 1  || monSFS.fe[nbFiles].name == '0' )
			continuer = false;
	}
	printf("pour un total de %d fichiers...\r\n",nbFiles);

	return 0;
}
