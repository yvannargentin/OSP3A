

void syscall_handler(uint syscall_nb, uint arg1, uint arg2, uint arg3, uint arg4) {
	// 1 : void print_string(char *str);
	// 2 : void read_string(char *buf);
	// 3 : void read_sector(int sector, uchar *buf);
	// 4 : void write_sector(int sector, uchar *buf);
	

	switch(syscall_nb) {

		case 1 :
			print_string(arg1);
		break;
		
		case 2 : 
			read_string(arg1);
		break;

		case 3 :
			read_sector(arg1, arg2);
		break;

		case 4 : 
			write_sector(arg1, arg2);
		break;
		

	} 
	

} 
