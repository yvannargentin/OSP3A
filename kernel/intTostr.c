#include "nomenclature.h"

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

void intTostr(char* s, int a, int length_str) {
	int taille_chaine = 1; 	

	int i;
	int puissance10, unite;
	int nb_numbers = length_str-1;
	for(i=0; i<nb_numbers; i++){
		puissance10 =a/myPow(10, nb_numbers-i-1);
		//unite = puisance10;

		// interrupt(0x80,print_str,"",0,0,0);
		print_string("");

		unite = modulo(puissance10, 10);

		// print_string("");

		s[i] = unite + 48; //48 = 0 en ascii;
	}
	s[length_str-1] = '\0';

	//print_string(s);
}

int lengthInt(int a){
	int length = 1;
	while(a/myPow(10, length) != 0){	
		length++;
	}
	length++;
	return length;
}

/*Example
	int test = 1234;
	
	int length_str = lengthInt(test);
	char str[length_str]; //espace prevu pour le \0
	intTostr(str, test, length_str);
}*/
