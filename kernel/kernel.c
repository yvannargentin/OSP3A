/*
*  kernel.c
*/

void print_str(char *buf);
void read_string(char *buf);
#define addr(idx, off) (idx * 256 + off)

void kernel(void)
{
	char *str;
	//print_str("entrez un caracteres :");
	read_string(str);
	//print_str(str);

	//init_syscalls(); // ecrase interruption 80 pour la notre
	//interrupt(0x80,1,str,0,0);
	while(1); 	// évite d'aller lire plus loin
}

void print_str(char *buf){ 
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
	int bx = addr(0x0, 0x07);
	
	// while loop set up 
	int i = 0; 
	char ascii = interrupt(0x16, 0, 0, 0, 0,0);
	int ax = addr(13, ascii);
	interrupt(0x10, ax, bx, 0, 0,0);

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
		interrupt(0x10, ax, bx, 0, 0,0);

		// clear the display when backspace is clicked 
		if(ascii==back){
			ax = addr(13, nullChar);
			interrupt(0x10, ax, bx, 0, 0,0);
			
			ax = addr(13, ascii);
			interrupt(0x10, ax, bx, 0, 0,0);
		}
	}

	// puts end line and null characters at the end of the array 
	buf[i] = endLine; 
	buf[i+1] = nullChar; 

	// Writes a new line character to the screen 
	ax = addr(13, endLine);
	interrupt(0x10, ax, bx, 0, 0,0); 
}
