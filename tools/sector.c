extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
extern void print_string(char *buf);

#define f(x, y) 256 * x + y
typedef unsigned char uchar;

void read_sector(int sector, uchar *buf){
	int ax = f(0x2, 1);
	int cx = f(0x0, sector);

	interrupt(0x13, ax , buf, cx , 0, 0); // int 13, ah=02/al=1, ch=0/cl=sector
	print_string(buf);
}


void write_sector(int sector, uchar *buf) {
	int ax = f(0x3, 1);
	int cx = f(0x0, sector);

	interrupt(0x13, ax , buf, cx, 0, 0); // int 13, ah=03/al=1, ch=0/cl=sector
	read_sector(sector, buf);
}
