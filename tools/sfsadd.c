/*
\file sfsadd.c
\brief this file content the fonction to add a file in the file system
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

#define MAX_CONTENT 1024
#define BLOCK 256
#define LENGTH_F 32
#define BIT 8
#define MAX_INDEX 111

int FileSize(char filename[LENGTH_F]);
bool LengthSupported(char filename[LENGTH_F]);

/*
This fonction read the content of the file in param and fill a buffer with it
\param filename the name of the file to read
\param buf the content of the file
\return return 0 if succeed and -1 if failure
*/
void sfsadd(SimpleFileSystem *sfs , char filename[LENGTH_F]){
	//check if the file is supported
	bool supported = LengthSupported(filename);
	if (supported == true){
		int i, j, r, h = 0;

		// read the file
		FILE *fp;
		fp = fopen(filename, "r");
		char content[MAX_CONTENT];
		bool fileInit = false;
		int nbindex = 0; // number of indexes we will have
		int length = 0;	

		// get the "id" of the file we wille had
		int idFiles = 0;
		while (sfs->fe[idFiles].size != 0)
			idFiles++;
	
		// read the bitmap
		for (i=0; i< BLOCK/BIT; i++){	
			for (j=0; j< BIT; j++){

				if (nbindex > MAX_INDEX)
					break;

				int bit = (sfs->bitmap[i]&(1<<j));
				if (bit == 0){ // if the bit of the bitmap is free
					if (fp == NULL){
						printf("impossible to open the file\n");
						return; 
					}else{
						sfs->bitmap[i] |= (1<<j) ; // bit block used

						// initalization of the file entry with the name and the length	
						if (fileInit == false){
							// get the name of the file
							while (filename[h] != '\0'){
								sfs->fe[idFiles].name[h] = filename[h];
								h++;
							}
							// get the size of the file
							sfs->fe[idFiles].size = FileSize(filename);
							fileInit = true;
						
						}
						// get the index in which we are going to put the content of the file
						int index = (i*BIT)+j+1;
						sfs->fe[idFiles].tabIndexes[nbindex] = index;

						// position where the content in fileContent stoped
						if (nbindex > 0)
							fseek(fp, ((MAX_CONTENT-1)*nbindex), 0);

						//fgets(content, MAX_CONTENT, fp); // get the content of the file
						fread(content, MAX_CONTENT, 1 ,  fp); // get the content of the file	

						// add the content int the fileContent matching to the index 
						for (r=0; r< MAX_CONTENT; r++){
							if ((content[r] == '\n') || (content[r] == '\r'))
								content[r] = ' ';
							sfs->fileContent[index][r] = content[r];
							length++;				
						}

						// See if we are at the end of the file
						if(length <= sfs->fe[idFiles].size){
							// empty the content of the rest
							for (r=0; r< MAX_CONTENT; r++)
								content[r] = 0;
							
							nbindex++; // next tabindex
						
						}else{
							fileInit = false;
							return;
						}
					}
				}
			
			}
		}
	}else{
		printf("Impossible to store %s in our File System (too big)\n",filename);
		return;	
	}
}

/*
This fonction get the size of a file
\param filename the name of the file to read
\return return the size 
*/
int FileSize(char filename[LENGTH_F]){
	// open to read
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("impossible to open the file\n");
		return; 
	}

	// calculate the length
	int length = 0;
	while(fgetc(fp) != EOF)
		length++;

	return length;
}

/*
This fonction check if the length of the file is supported by our File System
\param filename the name of the file to check
\return return true is supported and false is not
*/
bool LengthSupported(char filename[LENGTH_F]){
	int size = FileSize(filename);
	if (size > (MAX_INDEX * MAX_CONTENT))
		return false;
	return true;

}


