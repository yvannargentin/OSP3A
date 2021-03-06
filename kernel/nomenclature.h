/*
\file nomenclature.h
\brief this file content the defines, the typedef and the declaration of the fonction extern
*/

#define print_str 1
#define read_str 2
#define read_sect 3
#define write_sect 4
#define iter 5
#define get_st 6
#define read_f 7
#define remove_f 8
#define exe 9
#define SBStart 20
#define BtmStart 22
#define FeStart 24
#define FCStart FeStart + 32
#define FESize 256
#define BlockSize 512
#define TabIndexesStart 34
#define MaxFe 64
#define OffsetSize 32
#define NbTab 111
#define DRIVE 0x80

typedef unsigned char uchar;
typedef unsigned int uint;

/* structure who contain the stats
\struct stat_st
*/
typedef struct stat_st {
	char filename[32];
	int size;
} stat_st;

extern int strncpy(char *s1, const char *s2, size_t n, int var);
extern int lengthStr(char* tab);
extern int strcomp(const char *s1, const char *s2);
extern void intTostr(char* s, int a, int length_str);
extern int lengthInt(int a);

