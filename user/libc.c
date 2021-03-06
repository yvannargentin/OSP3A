/*
\file libc.c
\brief this file is an interface between the kernel nd the user
*/

#include "header.h"

/*
This fonction allows the user to make an interruption
\param number number of the interruption
\param arg1 1st argument of the interruption
\param arg2 2nd argument of the interruption
\param arg3 3rd argument of the interruption
\param arg4 4th argument of the interruption
*/
int syscall(uint number, uint arg1, uint arg2, uint arg3, uint arg4) {
	return interrupt(sys_handl, number,arg1,arg2,arg3,arg4);
}

////////////////////////////
// file related functions //
////////////////////////////


/*
This fonction allows the user to read a file's content
\param filename name of the file
\param buf content will be put into this variable
*/
int read_file(char *filename, uchar *buf){
	return syscall(sys_handl,read_f,filename,buf,0);
}

/*
This fonction allows the user to get the size of a file
\param filename name of the file
\param stat content will be put into this variable
*/
int get_stat(char *filename, stat_st *stat){
	return syscall(sys_handl,get_st,filename,0,0);
}

/*
This fonction allows the user to remove a file
\param filename name of the file
*/
int remove_file(char *filename){
	return syscall(sys_handl,remove_f,filename,0,0);
}

/////////////////
// io function //
/////////////////

/*
This fonction allows the user to read an user keyboard entry (string)
\param buf content will be put into this variable
*/
void read_string(char *buf){
	syscall(sys_handl,read_str,buf,0,0);
}

///////////////////////////////
// process control functions //
///////////////////////////////


/*
This fonction allows the user to execute a program
\param filename name of the file
\param segment segment number where the program should be saved to
*/
int exec(char *filename, uint segment){
	return syscall(sys_handl,exe,filename,segment,0);
}

/*
This fonction allows the user to exit a program by force
*/
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

/*
This fonction allows the user to copy a char* into another char*
\param dest char* where to content will be saved to
\param src char* source where the content is drawned
\param count number of char that have to be copied
*/
void memcpy(uchar *dest, uchar *src, uint count){

	uint i = 0;

	// check the length of dest
	if (strlen(dest) < count) count = strlen(dest);

	for (i = 0; i < count; i++){
		dest[i] = src[i];
	}
		
}

/*
This fonction allows the user to set all entries of a char* to a certain variable
\param dest char* where to content will be saved to
\param val char that will be repeated into dest
\param count number of char that have to be copied
*/
void memset(uchar *dest, uchar val, uint count){

	uint i = 0;

	// check the length of dest
	if(strlen(dest) < count) count = strlen(dest);

	for (i = 0; i < count; i++)
		dest[i] = val;
}

/*
This fonction get the length of a char*
\param s char to be inspected
\return return the length in uint format
*/
uint strlen(char *s){
	uint i = 0;
	while(s[i] !='\0')		
		i += 1;
	
	return i;
}

/*
This fonction copies the content of a char* into another
\param s1 char* source
\return char* the recepient of the copy
*/

char* strcpy(char *s1, char *s2){
	char *s1 = s2;
	int n = strlen(s2);
	while (n > 0) {
		*s++ = '\0';
		--n;
	}
	return s2;
}

/*
This fonction compares 2 char*
\param s1 char* first char* to be compared
\param s2 char* second char* to be compared
\return  0 if s1 and s2 are equals and 1 if not
*/

int strcmp(char *s1, char *s2){
	for ( ; *s1 == *s2; s1++, s2++){
		if (*s1 == '\0')
			return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

/*
This fonction allows a user to print a char*
\param str char* that has to be printed on the screen
\return  0 if no error
*/

int print_string(char *str){
	return syscall(sys_handl,print_str,str,0,0);
}

/*
This fonction allows a user to print an unsigned number
\param number uint that has to be printed
\return  0 if no error
*/

void print_uint(uint number){
	char *str;
	intTostr(str, number);
	syscall(sys_handl,print_str,str,0,0);
}

/*
This fonction makes one iteration in the fileEntry and fills buf with the corresponding content
\param isOk if = 1 we reached the end of the fileEntry => next call will start over to the first entry
\param buf will contain the content of the fileEntry we're iterating on
\return  0 if no error
*/

int iterator(int *isOk, char *buf){
	return syscall(sys_handl, iter,&isOk,buf,0,0);
}


