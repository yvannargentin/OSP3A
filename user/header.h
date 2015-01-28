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

// entetes des fonctions de la libc

int syscall(uint number, uint arg1, uint arg2, uint arg3, uint arg4);
int read_file(char *filename, uchar *buf);
int get_stat(char *filename, stat_st *stat);
int remove_file(char *filename);
void read_string(char *buf);
int exec(char *filename, uint segment);
void exit();
int lengthInt(int a);
void intTostr(char* s, int a);
void memcpy(uchar *dest, uchar *src, uint count);
void memset(uchar *dest, uchar val, uint count);
uint strlen(char *s);
char* strcpy(char *s1, char *s2);
int strcmp(char *s1, char *s2);
int print_string(char *str);
void print_uint(uint number);
int iterator(int *isOk, char *buf);
