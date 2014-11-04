extern int interrupt(int number, int ax, int bx, int cx, int dx, int di);

#define addr(idx, off) (idx * 256 + off)
void print_string(char *buf){ 
	int i=0; 
	int ax;
	int bx = addr(0x0, 0x07);
	for(i=0;buf[i]!='\0';i++){ 
		char al = buf[i];
		ax = addr(0x0E,buf[i]);
		interrupt(0x10, ax, bx, 0, 0,0);
	}
	
}
void read_string(char *buf){
	char enter = 0xd; 
	char endLine = 0xa; 
	char nullChar = 0x0; 
	char back = 0x8;
	
	// while loop set up 
	int i = 0; 
	char ascii = interrupt(0x16, 0, 0, 0, 0);
	int ax = addr(13, ascii);
	interrupt(10, ax, 0, 0, 0);

	// exit key: enter
	while(ascii!=enter){ 

		// decrements i (up to 0) if a backspace is entered, otherwise increments i
		// deals with what is in the char array         
		if(ascii==back&&i>0) {i--;}
		else if(ascii==back) {i=0;} 
		else {buf[i]=ascii; i++;}   

		// get next input letter and write it to screen 
		ascii = interrupt(0x16, 0, 0, 0, 0); 
		ax = addr(13, ascii);
		interrupt(0x10, addr(13,ascii), 0, 0, 0);

		// clear the display when backspace is clicked 
		if(ascii==back){
			ax = addr(13, nullChar);
			interrupt(0x10, ax, 0, 0, 0);
			
			ax = addr(13, ascii);
			interrupt(0x10, ax, 0, 0, 0);
		}
	}

	// puts end line and null characters at the end of the array 
	buf[i] = endLine; 
	buf[i+1] = nullChar; 

	// Writes a new line character to the screen 
	ax = addr(13, endLine);
	interrupt(0x10, ax, 0, 0, 0); 
}
