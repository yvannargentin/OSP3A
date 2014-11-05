/*
*  kernel.c
*/

void print_str(char *buf);
void read_string(char *buf);
#define addr(idx, off) (idx * 256 + off)

void kernel(void)
{
	char *str;
	//print_str("entrez un message :");
	//read_string(&str);
	//print_str(str);
	//print_string('a');
	init_syscalls(); // ecrase interruption 80 pour la notre
	interrupt(0x80,1,'a',0,0);
	interrupt(0x80,2,str,0,0);
	interrupt(0x80,1,str,0,0);

	while(1); 	// évite d'aller lire plus loin
}
