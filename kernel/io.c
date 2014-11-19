extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define pack(h, l) (h * 256 + l)

void print_char(char c) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x07);
	cx = pack(0, 1); //on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}

void print_string(char *buf){ 
	int i=0; 
	int ax, cx, bx;
	char al = buf;
	
	while(buf[i] !='\0'){
		print_char(buf[i]);
		i += 1;
	}
}

//affiche les caractères tapés au clavier
void read_string(char *buf){
	char ascii;
	int i = 0;
	while(ascii != 0xd){
		ascii = interrupt(0x16, 0, 0, 0, 0);
		print_string(ascii);
		buf[i] = ascii;
		i++;
	}
}
