#include "nomenclature.h"
extern int strcomp(const char *s1, const char *s2);
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

int read_file(char *filename, unsigned char *buf){
	int nb_sector_fe;
	int offset;
	unsigned char sect[512];
	int compteur = 0;

	// recuperer le secteur et l'offset du fe correponsdant
	do {
		
		if((compteur%2) == 1)
			nb_sector_fe++;
		if(offset == 0)
			offset = 256;
		else
			offset = 0;

		compteur++;

		interrupt(0x80,read_sect,nb_sector_fe, sect,0,0); // lit un secteur qu'on vient d'écrire 
		
	} while (strcomp(sect[offset]), filename);

	int debutTabIndexes = 34;
	buf = "";
	// parcours la liste des tabIndexes tant que != 0
	while (sect[debutIndexes] != 0){
		// lit contenu du filecontent a l'index correspondant
		int nb_sector_fc = debutFileContent + sect[debutIndexes];	
		unsigned char contenu1[512];
		unsigned char contenu2[512];
		
		interrupt(0x80,read_sect,nb_sector_fc, contenu1,0,0); 
		interrupt(0x80,read_sect,nb_sector_fc+1, contenu2,0,0);  
		
	
		// ajoute au buffer le contenu du filecontent
		buf += contenu1;
		buf += contenu2;
		nb_sector_fc += 2; 
		debutIndexes++;
	}
	
	return 0;	
}


int strcomp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	    return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}
