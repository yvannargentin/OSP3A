extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define addr(idx, off) (x * 256 + y)
void print_string(char *buf){
	int ax = addr(13, 1);
	int length = sizeof(*buf);
	int cx = addr(length, 0);
	interrupt(0x10, ax , buf, cx , 0, 0); // int 13, ah=13/al=1
}
