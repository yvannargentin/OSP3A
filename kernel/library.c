/*
\file nomenclature.h
\brief this file content the defines, the typedef and the declaration of the fonction extern
*/

#include "nomenclature.h"

/*
This fonction 
\param tab 
\return 
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
This fonction 
\param tab 
\return 
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
This fonction 
\param tab 
\return 
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
This fonction 
\param 
\return 
*/
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
This fonction 
\param 
\return 
*/
int strcomp(char *s1, char *s2) {
	for ( ; *s1 == *s2; s1++, s2++){
	if (*s1 == '\0')
		return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


