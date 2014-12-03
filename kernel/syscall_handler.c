extern void print_string(char *str);
extern void read_string(char *buf);
extern void read_sector(int sector, uchar *buf);
extern void write_sector(int sector, uchar *buf);
extern void iterator();
extern int get_stat(char *filename, struct stat_st *stat);
extern int read_file(char *filename, unsigned char *buf);
extern int remove_file(char *filename);


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

		case 1 :
			// arg1 = string
			print_string(arg1);
		break;
		
		case 2 : 
			//arg1 = buffer to hold user input
			read_string(arg1);
		break;

		case 3 :
			//arg1 = sector number
			//arg2 = buffer to hold read string
			read_sector(arg1, arg2);
		break;

		case 4 : 
			//arg1 = sector number
			//arg2 = buffer to hold read string
			write_sector(arg1, arg2);
		break;

		case 5 : 
			iterator();
		break;

		
		case 6 : 
			// arg1 = char *filename
			// arg2 = struct stat_st *stat
			get_stat(arg1,arg2);
		break;


		case 7 : 
			// arg1 = char *filename
			// arg2 = unsigned char *buf
			read_file(arg1,arg2);
		break;

		case 8 : 
			// arg1 = char *filename
			remove_file(arg1);
		break;
		
		default : print_string("invalid use of interruption 0x80");
		break;
		

	} 
	

} 


