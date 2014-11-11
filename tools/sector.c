extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
extern void print_string(char *buf);

#define f(x, y) 256 * x + y
typedef unsigned char uchar;

void read_sector(int sector, uchar *buf){
	int ax = f(0x02, 0x01);
	int cx = f(0x00, sector);
	int dx = f(0x00, 0x80);

	interrupt(0x13, ax , &buf, cx , dx, 0); // int 13, ah=02/al=1, ch=0/cl=sector
	// on peut pas lire des secteurs de moins de 512 et pas plus grand que 512.
	print_string(&ax);
}


void write_sector(int sector, uchar *buf) {
	int ax = f(0x3, 1);
	int cx = f(0x0, sector);

	interrupt(0x13, ax , buf, cx, 0, 0); // int 13, ah=03/al=1, ch=0/cl=sector
	read_sector(sector, buf);
}
