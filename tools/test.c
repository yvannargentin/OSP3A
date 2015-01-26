extern void print_string(char* buf);
extern void exit();

void test(){
	print_string("in test\0");
	exit();
}


