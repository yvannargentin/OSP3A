extern void print_string(char *str);
extern void read_string(char *buf);
extern void read_sector(int sector, uchar *buf);
extern void write_sector(int sector, uchar *buf);
extern int iterator(int counter, char *buf);
extern int get_stat(char *filename, struct stat_st *stat);
extern int read_file(char *filename, unsigned char *buf);
extern int remove_file(char *filename);
#include "nomenclature.h"

typedef unsigned int uint;

void syscall_handler(uint syscall_nb, uint arg1, uint arg2, uint arg3, uint arg4) {
	
	// 1 : void print_string(char *str);
	// 2 : void read_string(char *buf);
	// 3 : void read_sector(int sector, uchar *buf);
	// 4 : void write_sector(int sector, uchar *buf);
	// 5 : void iterator();
	// 6 : int get_stat(char *filename, struct stat_st *stat);
	// 7 : int read_file(char *filename, unsigned char *buf);
	// 8 : int remove_file(char *filename);
 
	switch(syscall_nb) {

		case print_str :
			// arg1 = string
			print_string(arg1);
		break;
		
		case read_str : 
			//arg1 = buffer to hold user input
			read_string(arg1);
		break;

		case read_sect :
			//arg1 = sector number
			//arg2 = buffer to hold read string
			sector(arg1, arg2, 0x42);
		break;

		case write_sect : 
			//arg1 = sector number
			//arg2 = buffer to hold read string
			sector(arg1, arg2, 0x43);
		break;

		case iter : 
			// arg1 = number of time it has been called
			// arg2 = buffer[512] for the answer
			iterator(arg1, arg2);
		break;

		
		case get_st : 
			// arg1 = char *filename
			// arg2 = struct stat_st *stat
			get_stat(arg1,arg2);
		break;


		case read_f : 
			// arg1 = char *filename
			// arg2 = unsigned char *buf
			read_file(arg1,arg2);
		break;

		case remove_f : 
			// arg1 = char *filename
			remove_file(arg1);
		break;
		
		default : print_string("invalid use of interruption 0x80");
		break;
		

	} 
	

} 


