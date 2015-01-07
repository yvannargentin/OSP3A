/*
\file libc.c
\brief this file is an interface between the kernel nd the user
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

int syscall(uint number, uint arg1, uint arg2, uint arg3, uint arg4) {
	return interrupt(0x80, number,arg1,arg2,arg3,arg4);
}


int read_file(char *filename, uchar *buf){
	return syscall(0x80,read_f,filename,buf,0,0);
}


int get_stat(char *filename, stat_st *stat){
	return syscall(0x80,get_st,filename,buf,0,0);
}


int remove_file(char *filename){
	return syscall(0x80,remove_f,filename,0,0,0);
}

read_string(char *buf){
	syscall(0x80,read_str,buf,0,0,0);
}

int exec(char *filename, uint segment){
	syscall(0x80,exe,filename,segment,0,0);
}

void exit(){
	
}
