#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

void sfsadd(SimpleFileSystem sfs , char filename[32]){
	int i, j, r, h;
	int block = 1024;
	
	// lecture du fichier et recuperation du contenu
	FILE *fp;
	fp = fopen(filename, "r");
	int taille = 10;
	char contenu[taille];
	bool fileInit = false;
		
	// lecture du bitmap
	for (i=0; i< block; i++){	
		for (j=0; j< 8; j++){
			if (sfs.bitmap[i]&(1<<j) == 0){ // si bit block libre
			
				if (fp == NULL){
					printf("impossible d'ouvrir le fichier");
					break; 
				}else{
					sfs.bitmap[i] &= (1<<j); // bit block utilisé
					// initalisation du file entry avec le nom et la taille	
					if (fileInit == false){
						for (j=0;j< 32; j++)
							sfs.fe[i].name[j] = filename[j];
					
						//printf("%s ", sfs.fe[i].name);
					
						// recuperer taille fichier
						//sfs.fe[i].size = ftell(fp);
						sfs.fe[i].size = 142;
						sfs.fe[i].tabIndexes[i] = i;
						//printf("%s ", sfs.fe[i].size);
						fileInit = true;
					}
				
					//printf(" block %d libre ", i);
					fgets(contenu, taille, fp); // recupere contenu fichier	

					// ajoute le contenu du fichier par block dans le fileContent correspondant
					for (j=0; j< taille; j++){
						sfs.fileContent[i][j] = contenu[j];
						//printf("%c", sfs.fileContent[i][j]);				
					}
				
					if(fgetc(fp) != EOF){
						// vide le tableau contenant le contenu
						memset (contenu, 0, taille); 
						// se positionne à l'endroit où le bout de contenu s'est arreter
						fseek(fp, taille,0); 
					}else
						break;
				}
			}
			
		}
	}
}
