extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);
extern void print_string(char *buf);

typedef unsigned char uchar;
typedef unsigned int uint;

// structure contenant le packet
typedef struct packet {
	uchar size;
	uchar reserved;
	uint sect_count;
	uint buf_offset;
	uint buf_segment;
	uint first_sect[4];
} packet;

void sector(int sector_number, uchar *buf, int interruption){

	packet p;
	p.size = 0x10;
	p.reserved = 0;
	p.sect_count = 1;
	p.buf_offset = buf;
	//p.buf_segment => segment is set in the asm code
	p.first_sect[0] = sector_number;
	p.first_sect[1] = 0;
	p.first_sect[2] = 0;
	p.first_sect[3] = 0;

	sector_raw(interruption, 0x80, &p); // BOOT_DRIVE = 0x80
	//p.buf_offset =  p.buf_offset + '\0';
	print_string(p.buf_offset);
}

/*
void write_sector(int sector_number, uchar *buf) {
	packet p;
	p.size = 0x10;
	p.reserved = 0;
	p.sect_count = 1;
	p.buf_offset = buf;
	//p.buf_segment => segment is set in the asm code
	p.first_sect[0] = sector_number;
	p.first_sect[1] = 0;
	p.first_sect[2] = 0;
	p.first_sect[3] = 0;

	write_sector_raw(0x80, &p); // BOOT_DRIVE = 0x80
}*/
