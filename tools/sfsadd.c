
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

#define TAILLE 10
#define BLOCK 256
#define LENGTH 32
#define BIT 8
#define MAX_INDEX 111

int FileSize(char filename[LENGTH]);
bool LengthSupported(char filename[LENGTH]);

void sfsadd(SimpleFileSystem *sfs , char filename[LENGTH]){
	// verifie que l'on peut stocker le fichier 
	bool supported = LengthSupported(filename);
	if (supported == true){
		int i, j, r, h = 0;

		// lecture du fichier et recuperation du contenu
		FILE *fp;
		fp = fopen(filename, "r");
		char contenu[TAILLE];
		bool fileInit = false;
		int nbindex = 0; // nombre de tabIndexes qu'on aura dans le file entry
		int taille = 0;	

		// recupere l'id du fichier pour l'ajouter 
		int idFiles = 0;
		while (sfs->fe[idFiles].size != 0)
			idFiles++;
	
		// lecture du bitmap
		for (i=0; i< BLOCK/BIT; i++){	
			for (j=0; j< BIT; j++){

				if (nbindex > MAX_INDEX)
					break;
				printf("j %d bitmap %d ", (1<<j), sfs->bitmap[i]);
				int bit = (sfs->bitmap[i]&(1<<j));
			
				//printf("%d : ", bit);
				if (bit == 0){ // si bit block libre
					if (fp == NULL){
						printf("impossible d'ouvrir le fichier\n");
						return; 
					}else{
						sfs->bitmap[i] &= (1<<j) ; // bit block utilisé
						printf("bitmap pris %d \n", sfs->bitmap[i]);

						// initalisation du file entry avec le nom et la taille	
						if (fileInit == false){
							// recupere le nom du fichier
							while (filename[h] != '\0'){
								sfs->fe[idFiles].name[h] = filename[h];
								h++;
							}
							// recuperer taille fichier
							sfs->fe[idFiles].size = FileSize(filename);
							fileInit = true;
						
						}
						// recupere l'index dans lequel est pour ranger le contenu (filecontent)
						int index = (i*BIT)+j+1;
						sfs->fe[idFiles].tabIndexes[nbindex] = index;	
						printf("filecontent pris %d \n", index);
						//printf("%d %d %s\n ", index, i, filename);

						// se positionne à l'endroit où le bout de contenu s'est arreter
						if (nbindex > 0)
							fseek(fp, ((TAILLE-1)*nbindex), 0);

						fgets(contenu, TAILLE, fp); // recupere contenu fichier	

						// ajoute le contenu du fichier par block dans le fileContent correspondant
						for (r=0; r< TAILLE; r++){
							sfs->fileContent[index][r] = contenu[r];
							taille++;				
						}

						// tant qu'on arrive pas à la fin du fichier
						if(taille <= sfs->fe[idFiles].size){
							// vide le tableau contenant le contenu
							for (r=0; r< TAILLE; r++)
								contenu[r] = 0;
							
							nbindex++; // prochain tabindex
						
						}else{
							fileInit = false;
							return;
						}
					}
				}
			
			}
		}
	}else{
		printf("Impossible de stocker %s dans notre systeme de fichier car il est trop grand\n",filename);
		return;	
	}
}

// Calcule la taille du fichier
int FileSize(char filename[LENGTH]){
	// ouvre le fichier pour le parcourir
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("impossible d'ouvrir le fichier\n");
		return; 
	}

	// calcul la taille du fichier
	int taille = 0;
	while(fgetc(fp) != EOF)
		taille++;

	return taille;
}

// Verifie si la taille du fichier peut être stoquer dans le systeme
bool LengthSupported(char filename[LENGTH]){
	int size = FileSize(filename);
	if (size > (MAX_INDEX * TAILLE))
		return false;
	return true;

}


