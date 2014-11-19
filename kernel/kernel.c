/*
*  kernel.c
*/

#define addr(idx, off) (idx * 256 + off)

char *str;

void kernel(void)
{
	
	// print_string(str); 	// fonctionne
	init_syscalls(); 	// ecrase interruption 80 pour la notre
	interrupt(0x80,1,"abcd",0,0);
	
	while(1) {
		interrupt(0x80,2,str,0,0);
		interrupt(0x80,1,str,0,0);
	}
	while(1); 	// évite d'aller lire plus loin
}

