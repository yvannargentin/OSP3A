extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define addr(idx, off) (idx * 256 + off)
void print_string(char *buf){ 
	int i=0; 
	int ax, cx, bx;

	//while(buf[i] != '\0')	{
		char al = buf;
		ax = addr(0x0e, al);
		bx = addr(0x00, 0x07);
		cx = addr(0, 1); //on affiche 1 caractère
		interrupt(0x10, ax, bx, cx, 0,0);
	//}
	
}

//affiche les caractères tapés au clavier
void read_string(char *buf){
	char ascii;
	
	while(ascii != 0xd){
		ascii = interrupt(0x16, 0, 0, 0, 0);
		print_string(ascii);
	}
}
