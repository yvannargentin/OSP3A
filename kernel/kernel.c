/*
*  kernel.c
*/

void kernel(void)
{
	char *str = "costa ricaaa";
	init_syscalls(); // ecrase interruption 80 pour la notre
	interrupt(0x80,1,str,0,0,0);
	while(1); 	// évite d'aller lire plus loin
}
