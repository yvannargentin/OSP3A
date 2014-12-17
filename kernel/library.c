/*
\file library.c
\brief this file content the fonctions we write that we need in our other fonctions
*/

#include "nomenclature.h"

/*
This fonction calculate the pow of 2 int
\param a the integer that we want to pow
\param b the integer that we pow on a
\return return the pow
*/
int myPow(int a,int b){
      if(b<0)      
        return (1/a)*(myPow(a,b+1)); 
      else if(b==0)
        return 1;
      else if(b==1)
        return a;
      else
        return a*myPow(a,b-1);
}

/*
This fonction change a int to a string so we can print it
\param s the string that we fill
\param a the int that we want to change to a string
\param length_str length of the int 
*/
void intTostr(char* s, int a, int length_str) {
	int taille_chaine = 1; 	

	int i;
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
This fonction copy the content of a string into another
\param s1 the buffer were we copy
\param s2 the buffer that we copy
\param n the length of the buffer s2
\return the buffer s1
*/

// !\/! //
// Tu n'as pas besoin de retourner s1 il est modifié car tu envoie un pointeur à ta fonction ana
// !\/! //
char* strncpy(char *s1, char *s2, int n){
    char *s = s1;
    while (n > 0 && *s2 != '\0') {
	*s++ = *s2++;
	--n;
    }
    while (n > 0) {
	*s++ = '\0';
	--n;
    }
    return s1;
}

/*
This fonction copy the content of a buf into another without stopping if it encounters a \0
\param s1 the buffer were we copy
\param s2 the buffer that we copy
\param n the length of the buffer s2
\return the buffer s1
*/
int strcpy(char *s1, char *s2, int n){
    char *s = s1;
    while (n > 0) {
	*s++ = *s2++;
	--n;
    }
    while (n > 0) {
	*s++ = '\0';
	--n;
    }
    return 0;
}

/*
This fonction get the length of a string
\param tab the content of the file
\return return the length
*/
int lengthStr(char* tab){
	int i = 0;
	while(tab[i] !='\0')		
		i += 1;
	
	return i;
}

/*
This fonction check if 2 string are equals
\param s1 the string we want to compare
\param s2 the string we want to compare
\return return 0 if equals
*/
int strcomp(char *s1, char *s2) {
	for ( ; *s1 == *s2; s1++, s2++){
	if (*s1 == '\0')
		return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


