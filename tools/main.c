#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "structure.h"

extern SimpleFileSystem sfscreate (char *sfsName);
extern void sfsadd(SimpleFileSystem *sfs , char filename[32]);
extern void sfsls(SimpleFileSystem sfs);
extern void sfsdel(SimpleFileSystem *sfs, char filename[32]);

void sfsimg (SimpleFileSystem sfs){
	int file = open("fs.img", O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
	write(file, &sfs.sb, 18);
	
	//Remplir le reste du block avec des 0	
	int i;
	char j = 0;
	int borne = 1024-18;	
	for(i=0;i<borne;i++) {
		write(file, &j, 1);
	}
	write(file, &sfs.bitmap, 1024);

	int nbFE = 0;
	int id = 0;
	//Recuperation du nombre de FE
	while (sfs.fe[id++].size != 0)
		nbFE++;

	write(file, &sfs.fe, 256*nbFE);
	//Remplir le reste du block avec des 0
	borne = (1024*16)-(256*nbFE);
	for(i=0;i<borne;i++) {
		write(file, &j, 1);
	}
	

	write(file, &sfs.fileContent, 1024*256);
	close(file);
}

int main(int argc, char **argv){
	SimpleFileSystem sf = sfscreate("sfs");
	sfsadd(&sf, "test.txt\0");
	sfsadd(&sf, "fichier.txt\0");
	sfsls(sf);
	//sfsdel(&sf, "test.txt");
	//sfsls(sf);
	sfsimg(sf);
}
