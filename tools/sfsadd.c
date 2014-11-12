#include <stdio.h>
#include <string.h>
#define block 1024

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

typedef struct SimpleFileSystem {
	SuperBlock sb;
	char bitmap[1024];
	FileEntries fe;
	char fileContent[256][1024];
} SimpleFileSystem;


SimpleFileSystem init(){
	SimpleFileSystem sfs;
	strcpy(sfs.sb.signature, "SFSv0100");
	sfs.sb.nbSecteurs = 2;
	sfs.sb.tailleBitmap = 1;
	sfs.sb.tailleFE = 256;
	sfs.sb.blockReservedFE = 16;
	sfs.sb.blockReserverContent = 256;

	//Remplir bitmap que avec des 0
	int i;
	for(i=0; i<sizeof(sfs.bitmap); i++){
		sfs.bitmap[i] = '1';
	}
	sfs.bitmap[32] = '0';
	return sfs;

	
}

void sfsadd(SimpleFileSystem sfs , char filename[32], char contenu[1024]){
	int i, j, r, h;
	// initalisation du file entry avec le nom et la taille	
	for (j=0;j< 32; j++){
		if (filename[j] == '\0'){
			for (r = j; r < (32 - j); r++){
				sfs.fe.name[r] = '0';
			}
			break;
		} else
			sfs.fe.name[j] = filename[j];
	}

	sfs.fe.size = 10;
	//printf("size%d\n", sfs.fe.size);

	
	for (i=0; i< block; i++){
		if (sfs.bitmap[i] == '0'){ // si block libre
			
			sfs.fe.tabIndexes[i] = i;
			//printf("%d", sfs.fe.tabIndexes[i]);
			for (j=0; j< sizeof(contenu); j++){
				sfs.fileContent[i][j] = contenu[j];
				//printf("%c", sfs.fileContent[i][j]);				
			}
		}
			
	}
}

int main(){
	SimpleFileSystem sfs = init();
	sfsadd(sfs, "test.txt\0", "hello");
	return 0;
}
