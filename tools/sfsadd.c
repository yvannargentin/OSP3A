#include <stdio.h>
#define block 1024

struct fileEntry {
	char Name[32];
	int Size;
	int TabIndexes[16];

};


typedef struct fileEntry fe;

struct SysFileSimple {
	char superblock[block] ;
	char bitmap[block] ;
	fe fileEntry;
	char fileContent[block] ;
};

typedef struct SysFileSimple SysFichier;

SysFichier init(){
	SysFichier sf;
	int i;	
	for (i=0; i< block; i++)
		sf.bitmap[i] = '1';

	
	sf.bitmap[32] = '0';
	for (i=0; i< 16;i++)
		sf.fileEntry.TabIndexes[i] = 0;

	return sf;

	
}

void sfsadd(SysFichier sfs , char filename[32], char contenu){
	int i, j, r;
	// initalisation du file entry avec le nom et la taille	
	for (j=0;j< 32; j++){
		if (filename[j] == '\0'){
			for (r = j; r < (32 - j); r++)
				sfs.fileEntry.Name[r] = '0';
			break;
		} else
			sfs.fileEntry.Name[j] = filename[j];
	}

	sfs.fileEntry.Size = 10;
	printf("%d\n", sfs.fileEntry.Size);

	for (j=0;j< 32; j++)
		printf("%c", sfs.fileEntry.Name[j]);
	
	for (i=0; i< block; i++){
		if (sfs.bitmap[i] == '0'){ // si block libre
			
			sfs.fileEntry.TabIndexes[i] = i;
			sfs.fileContent[i] = contenu;
			printf("%c", sfs.fileContent[i]);
		}
			
	}
}

int main(){
	SysFichier sfs = init();
	sfsadd(sfs, "test.txt\0", 'h');
	return 0;
}
