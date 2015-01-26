/*
\file sfsadd.c
\brief this file content the fonction to add a file in the file system
*/
#include "structure.h"

extern SimpleFileSystem sfscreate (char *sfsName);
extern void sfsadd(SimpleFileSystem *sfs , char filename[LENGTH_F]);
extern void sfsls(SimpleFileSystem sfs);
extern void sfsdel(SimpleFileSystem *sfs, char filename[LENGTH_F]);

/*
This fonction create the image of the sfs
\param sfs the sfs to put in the image
*/
void sfsimg (SimpleFileSystem sfs){
	int file = open("fs.img", O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
	write(file, &sfs.sb, LENGTH_SB );
	
	//Remplir le reste du block avec des 0	
	int i;
	char j = 0;
	int borne = MAX_CONTENT-LENGTH_SB ;	
	for(i=0;i<borne;i++) {
		write(file, &j, 1);
	}
	write(file, &sfs.bitmap, MAX_CONTENT);

	int nbFE = 0;
	int id = 0;
	//Recuperation du nombre de FE
	while (sfs.fe[id++].size != 0)
		nbFE++;

	write(file, &sfs.fe, BLOCK*nbFE);
	//Remplir le reste du block avec des 0
	borne = (MAX_CONTENT*ReservedFE)-(BLOCK*nbFE)

;
	for(i=0;i<borne;i++) {
		write(file, &j, 1);
	}
	

	write(file, &sfs.fileContent, MAX_CONTENT*BLOCK);
	close(file);
}

/*
This is the main fonction
\param argc number of args passed in parameter
\param argv args passed in parameter
\return return 0 
*/
int main(int argc, char **argv){
	SimpleFileSystem sf = sfscreate("sfs");
	sfsadd(&sf, "test.txt\0");
	sfsadd(&sf, "fichier.txt\0");
	sfsadd(&sf, "test.c\0");
	sfsadd(&sf, "test.o\0");
	sfsadd(&sf, "test.bin\0");
	sfsls(sf);
	//sfsdel(&sf, "test.txt");
	//sfsls(sf);
	sfsimg(sf);
}
