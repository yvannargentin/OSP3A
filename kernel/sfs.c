int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define pack(h, l) (h * 256 + l)

void iterator() {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); 	//Page number + foreground color
	cx = pack(0, 1); 	//on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}

int get_stat(char *filename, struct stat_st *stat) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); 	//Page number + foreground color
	cx = pack(0, 1); 	//on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}

int read_file(char *filename, unsigned char *buf) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); 	//Page number + foreground color
	cx = pack(0, 1); 	//on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}

int remove_file(char *filename) {
	int ax, cx, bx;
	char al = c;
	ax = pack(0x0e, c);
	bx = pack(0x00, 0x00); 	//Page number + foreground color
	cx = pack(0, 1); 	//on affiche 1 caractère
	interrupt(0x10, ax, bx, cx, 0,0);
}
