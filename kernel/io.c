extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define pack(h, l) (h * 256 + l)

void print_char(char c) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); //Page number + foreground color
	cx = pack(0, 1); //on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}

void print_string(char *buf){ 
	int i=0; 
	char al = buf;
	
	while(buf[i] !='\0'){//Parcours de la chaine
		print_char(buf[i]); //Affichage d'un seul caractère
		i += 1;
	}
	print_char(10); //Nouvelle ligne
	print_char(13); //Retour chariot
}

//affiche les caractères tapés au clavier
void read_string(char *buf){
	char ascii; //Variable qui va receptionner l'entrée clavier
	int i = 0;//Initialisation du début de la chaine "buf"
	while(ascii != 0xd){ //Boucle tant que la touche "enter" n'est pas pressé
		ascii = interrupt(0x16, 0, 0, 0, 0); //Appel bloquant attendant un caractère
		print_char(ascii); //Affichage du caractère tappé
		buf[i] = ascii; //Ajout du caractère tapé au buffer
		i++;
	}
	buf[i] = '\0'; //indique la fin de la chaine
	print_char(10); //Nouvelle ligne
	print_char(13); //Retour chariot
}
