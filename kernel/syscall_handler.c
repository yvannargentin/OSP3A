/*
\file syscall_handler.c
\brief this file content a switch who call the right fonction in fonction of interrupt
*/

#include "nomenclature.h"

extern int print_string(char *str);
extern int read_string(char *buf);
extern int read_sector(int sector, uchar *buf);
extern int write_sector(int sector, uchar *buf);
extern int iterator(int* isOk, char *buf);
extern int get_stat(char *filename, struct stat_st *stat);
extern int read_file(char *filename, unsigned char *buf);
extern int remove_file(char *filename);

/*
This fonction content the switch 
\param syscall_nb the call we want
\param arg1.. arg4 the variables that we have to pass to a the fonction
*/
int syscall_handler(uint syscall_nb, uint arg1, uint arg2, uint arg3, uint arg4) {
 
	switch(syscall_nb) {

		case print_str :
			// arg1 = string
			return print_string(arg1);
		break;
		
		case read_str : 
			//arg1 = buffer to hold user input
			return read_string(arg1);
		break;

		case read_sect :
			//arg1 = sector number
			//arg2 = buffer to hold read string
			return sector(arg1, arg2, 0x42);
		break;

		case write_sect : 
			//arg1 = sector number
			//arg2 = buffer to hold read string
			return sector(arg1, arg2, 0x43);
		break;

		case iter : 
			// arg1 = number of time it has been called
			// arg2 = buffer[512] for the answer
			return iterator(arg1, arg2);
		break;

		
		case get_st : 
			// arg1 = char *filename
			// arg2 = struct stat_st *stat
			return get_stat(arg1,arg2);
		break;


		case read_f : 
			// arg1 = char *filename
			// arg2 = unsigned char *buf
			return read_file(arg1,arg2);
		break;

		case remove_f : 
			// arg1 = char *filename
			return remove_file(arg1);
		break;

		
		case exe : 
			// arg1 = char *filename
			return execute(arg1);
		break;
		
		default : print_string("invalid use of interruption 0x80");
			return -1;
		break;
		

	} 
	

} 


