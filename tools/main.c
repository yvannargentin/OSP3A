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
	printf("%d\n", sfs.sb.nbSecteurs);
	write(file, &sfs.sb, 1024);
	write(file, &sfs.bitmap, 1024);
	write(file, &sfs.fe, 1024*16);
	write(file, &sfs.fileContent, 1024);
	close(file);
}

int main(int argc, char **argv){
	SimpleFileSystem sf = sfscreate("sfs");
	sfsadd(&sf, "test.txt\0");
	sfsadd(&sf, "fichier.txt\0");
	sfsls(sf);
	sfsdel(&sf, "test.txt");
	sfsls(sf);
	sfsimg(sf);
}
