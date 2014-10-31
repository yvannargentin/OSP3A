/*
*  kernel.c
*/

extern void init_syscalls();

void kernel(void)
{
	init_syscalls(); // ecrase interruption 80 pour la notre
	char *str = "costaaa riiiiicaaaaa";
	interrupt(0x80,1,str,0,0);
	while(1); // évite d'aller lire plus loin
}
