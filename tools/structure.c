#include <string.h>

struct SuperBlock{
	char signature[8];
	int nbSecteurs;
	int tailleBitmap;
	int tailleFE; //FE = FileEntry
	int blockReservedFE;
	int blockReserverContent;
};

struct Bitmap{
	char blockUtilises[1024];
};

struct FileEntries{
	char name[32];
	int size;
	int tabIndexes[111]; //111 = (tailleFE-name-size)/2
};

int main (int argc, char *argv){
	struct SuperBlock sp;
	struct Bitmap b;
	struct FileEntries fe;

	
	strcpy(sp.signature, "SFSv0100");
	sp.nbSecteurs = 2;
	sp.tailleBitmap = 1;
	sp.tailleFE = 256;
	sp.blockReservedFE = 16;
	sp.blockReserverContent = 16;

	//Remplir que avec des 0
	//b.blockUtilises = { [0..1023] = 0};

	//char superblock_string[18] }
}
