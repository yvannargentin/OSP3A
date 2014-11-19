/*
*  kernel.c
*/


void kernel(void) {
	char *str;
	
	init_syscalls(); 		// ecrase interruption 80 pour la notre
	interrupt(0x80,1,"abcd",0,0);
	
	// Lit une string et l'ecrit
	while(1) {
		interrupt(0x80,2,str,0,0);
		interrupt(0x80,1,str,0,0);
		str = "";
	}
	while(1); 	// évite d'aller lire plus loin
}

