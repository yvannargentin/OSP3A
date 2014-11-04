extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define addr(idx, off) (idx * 256 + off)
void print_string(char *buf){
	int ax = addr(13, 1);
	int length = sizeof(*buf);
	int cx = addr(length, 0);
	interrupt(0x10, ax , buf, cx , 0, 0); // int 13, ah=13/al=1
}

void read_string(char *buf){
	int i = 0;
	int ax = addr(0, 0);
	//Tant que le scan code n'est pas égal à 1C0D
	//while((ax>>8) != 1C0D){	
		ax = addr(0, 0);
		interrupt(0x16, &ax , 0, 0 , 0, 0); // int 13, ah=0/al=0
		buf[i++] = (ax<<8)>>8;
	//}
}
