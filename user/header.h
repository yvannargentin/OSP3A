typedef unsigned char uchar;
typedef unsigned int uint;

#define print_str 1
#define read_str 2
#define read_sect 3
#define write_sect 4
#define iter 5
#define get_st 6
#define read_f 7
#define remove_f 8
#define exe 9
#define sys_handl 0x80

/* structure who contain the stats
\struct stat_st
*/
typedef struct stat_st {
	char filename[32];
	int size;
} stat_st;
