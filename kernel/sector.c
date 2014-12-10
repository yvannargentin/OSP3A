/*
\file sector.c
\brief this file content the fonction to read or write sectors 
*/

typedef unsigned char uchar;
typedef unsigned int uint;

/* structure who contain the packet
\struct packet
*/
typedef struct packet {
	uchar size;
	uchar reserved;
	uint sect_count;
	uint buf_offset;
	uint buf_segment;
	uint first_sect[4];
} packet;

/*
This fonction read or write a sector in fonction of the interruption
\param sector_number the sector in the image
\param buf the content of the sector
\param interruption 0x42 to read or 0x43 to write
*/
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

	sector_raw(interruption, 0x80, &p);
}
