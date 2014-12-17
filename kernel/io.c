/*
\file io.c
\brief this file content the fonctions of the in/out
*/

extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define pack(h, l) (h * 256 + l)

/*
This fonction print a char with the interruption 10
\param c character that we print
*/
int print_char(char c) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); 	//Page number + foreground color
	cx = pack(0, 1); 	//print 1 character
	interrupt(0x10, ax, bx, cx, 0,0);
	return 0;
}

/*
This fonction print a string using print_char
\param bug string that we print
*/
int print_string(char *buf){ 
	int i=0; 
	char al = buf;

	while(buf[i] !='\0'){		//Parcours de la chaine
		print_char(buf[i]); 	//Affichage d'un seul caractère
		i += 1;
	}
	print_char(10); //Nouvelle ligne
	print_char(13); //Retour chariot
	return 0;
}

/*
This fonction print the character typed
\param bug string that we fill
*/
int read_string(char *buf){
	char ascii; 		//Variable qui va receptionner l'entrée clavier
	int i = 0;		//Initialisation du début de la chaine "buf"
	while(ascii != 0xd){ 	//Boucle tant que la touche "enter" n'est pas pressé
		ascii = interrupt(0x16, 0, 0, 0, 0); 	//Appel bloquant attendant un caractère
		print_char(ascii); 	//Affichage du caractère tappé
		buf[i] = ascii; 	//Ajout du caractère tapé au buffer
		i++;
	}
	buf[i] = '\0'; 	//indique la fin de la chaine
	print_char(10); //Nouvelle ligne
	print_char(13); //Retour chariot
	return 0;
}
