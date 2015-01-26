/*
\file libc.c
\brief this file is an interface between the kernel nd the user
*/

#include "header.h"


int syscall(uint number, uint arg1, uint arg2, uint arg3, uint arg4) {
	return interrupt(sys_handl, number,arg1,arg2,arg3,arg4);
}


int read_file(char *filename, uchar *buf){
	return syscall(sys_handl,read_f,filename,buf,0);
}


int get_stat(char *filename, stat_st *stat){
	return syscall(sys_handl,get_st,filename,0,0);
}


int remove_file(char *filename){
	return syscall(sys_handl,remove_f,filename,0,0);
}

// io function
void read_string(char *buf){
	syscall(sys_handl,read_str,buf,0,0);
}

int exec(char *filename, uint segment){
	return syscall(sys_handl,exe,filename,segment,0);
}

void exit(){
	// exit from a program
	
}

//////////////////////
// string functions //
//////////////////////

/*
This fonction get the length of a integer
\param a the integer we want to know the length
\return return the length
*/
int lengthInt(int a){
	int length = 1;
	while(a/myPow(10, length) != 0){	
		length++;
	}
	length++;
	return length;
}


/*
This fonction change a int to a string so we can print it
\param s the string that we fill
\param a the int that we want to change to a string
\param length_str length of the int 
*/
void intTostr(char* s, int a) {
	int taille_chaine = 1; 	
	int i;
	int length_str = lengthInt(a);
	int puissance10, unite;
	int nb_numbers = length_str-1;
	for(i=0; i<nb_numbers; i++){
		puissance10 =a/myPow(10, nb_numbers-i-1);
		unite = modulo(puissance10, 10);
		s[i] = unite + 48; //48 = 0 en ascii;
	}
	s[length_str-1] = '\0';

	/*Example
	int test = 1234;
	
	int length_str = lengthInt(test);
	char str[length_str]; //espace prevu pour le \0
	intTostr(str, test, length_str);
	*/
}


void memcpy(uchar *dest, uchar *src, uint count){

	uint i = 0;

	// check the length of dest
	if (strlen(dest) < count) count = strlen(dest);

	for (i = 0; i < count; i++){
		dest[i] = src[i];
	}
		
}

void memset(uchar *dest, uchar val, uint count){

	uint i = 0;

	// check the length of dest
	if(strlen(dest) < count) count = strlen(dest);

	for (i = 0; i < count; i++)
		dest[i] = val;
}

uint strlen(char *s){
	uint i = 0;
	while(s[i] !='\0')		
		i += 1;
	
	return i;
}

char* strcpy(char *s1, char *s2){
	char *s = s1;
	int n = strlen(s1);
	while (n > 0) {
		*s++ = '\0';
		--n;
	}
	return 0;
}

int strcmp(char *s1, char *s2){
	for ( ; *s1 == *s2; s1++, s2++){
		if (*s1 == '\0')
			return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


int print_string(char *str){
	return syscall(0x80,print_str,str,0,0);
}

void print_uint(uint number){
	char *str;
	intTostr(str, number);
	syscall(0x80,print_str,str,0,0);
}
