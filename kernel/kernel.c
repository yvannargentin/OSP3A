/*
*  kernel.c
*/

extern void init_syscalls();
extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
void print_str(char *buf);

#define addr(idx, off) (idx * 256 + off)

void kernel(void)
{
	char *str = "costa ricaaa";
	init_syscalls(); // ecrase interruption 80 pour la notre
	print_str(str);
	interrupt(0x80,1,&str,0,0,0);
	while(1); 	// évite d'aller lire plus loin
}

void print_str(char *buf){ 
	int i=0; 
	int ax;
	int bx = addr(0x0, 0x07);
	for(i=0;buf[i]!='\0';i++){ 
		char al = buf[i];
		ax = addr(0x0E,buf[i]);
		interrupt(0x10, ax, bx, 0, 0,0);
	}
	
}
