#include <string.h>
#include <stdio.h>

typedef struct SuperBlock{
	char signature[8];
	int nbSecteurs;
	int tailleBitmap;
	int tailleFE; //FE = FileEntry
	int blockReservedFE;
	int blockReserverContent;
} SuperBlock;

typedef struct FileEntries{
	char name[32];
	int size;
	int tabIndexes[111]; //111 = (tailleFE-name-size)/2
} FileEntries;

typedef struct sfs {
	SuperBlock sb;
	char bitmap[1024];
	FileEntries fe;
	char fileContent[256][1024];
} SimpleFileSystem;

 

int ls(sfs monSFS) {
	int nbFiles = 0;
	bool continuer = true;
	printf(" - Nom - Taille -\r\n");
	while(continuer){
		printf(" - %s - %d -\r\n",monSFS.FileEntries.Name,monSFS.FileEntries.Size);
		nbFiles++;
	}
	printf("pour un total de %d fichiers...\r\n",nbFiles);

	return 0;
}
