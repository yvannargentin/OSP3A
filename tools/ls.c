int ls(int argc, char ** argv) {
	struct Superblock mySuperBlock;
	struct Bitmap myBitmap;
	struct FileEntry MyFileEntry;
	int nbFiles = 0;
	bool continuer = true;
	printf(" - Nom - Taille -\r\n");
	while(continuer){
		printf(" - %s - %d -\r\n",MyFileEntry.Name,MyFileEntry.Size);
		nbFiles++;
	}
	printf("pour un total de %d fichiers...\r\n",nbFiles);

	return 0;
}
