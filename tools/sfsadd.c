#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

void sfsadd(SimpleFileSystem sfs , char filename[32]){
	int i, j, r, h;
	int block = 256/8;
	
	// lecture du fichier et recuperation du contenu
	FILE *fp;
	fp = fopen(filename, "r");
	int taille = 10;
	char contenu[taille];
	bool fileInit = false;
		
	// lecture du bitmap
	for (i=0; i< block; i++){	
		for (j=0; j< 8; j++){
			
			if ((sfs.bitmap[i]&(1<<j)) == 0){ // si bit block libre
				if (fp == NULL){
					printf("impossible d'ouvrir le fichier");
					break; 
				}else{
					sfs.bitmap[i] &= (1<<j); // bit block utilisé
					// initalisation du file entry avec le nom et la taille	
					if (fileInit == false){
						for (h=0;h< 32; h++)
							sfs.fe[i].name[h] = filename[h];
					
						printf("%s ", sfs.fe[i].name);
					
						// recuperer taille fichier
						//sfs.fe[i].size = ftell(fp);
						sfs.fe[i].size = 142;
						sfs.fe[i].tabIndexes[i] = i;
						printf("%d ", sfs.fe[i].size);
						fileInit = true;
					}
				
					//printf(" block %d libre ", i);
					fgets(contenu, taille, fp); // recupere contenu fichier	

					// ajoute le contenu du fichier par block dans le fileContent correspondant
					for (r=0; r< taille; r++){
						int index = (i*8)+j-1;
						sfs.fileContent[index][r] = contenu[r];
						printf("%c", sfs.fileContent[index][r]);				
					}
				
					// tant qu'on arrive pas à la fin du fichier
					if(fgetc(fp) != EOF){
						// vide le tableau contenant le contenu
						memset (contenu, 0, taille); 
						// se positionne à l'endroit où le bout de contenu s'est arreter
						fseek(fp, taille-1,0); 
					}else{
						
						printf("\n");	
						fileInit = false;
						break;
					}
				}
				if(fgetc(fp) == EOF)
					break;
			}
			
		}
	}
}
