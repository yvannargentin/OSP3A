#include <stdio.h>
int myPow(int a,int b){
      if(b<0)      
        return (1.0/a)*(myPow(a,b+1)); 
      else if(b==0)
        return 1;
      else if(b==1)
        return a;
      else
        return a*myPow(a,b-1);
}

void intTostr(char* s, int a) {
	int taille_chaine = 1; 	
		
	while(a/myPow(10, taille_chaine) != 0){	
		taille_chaine++;
	}

	char result[taille_chaine+1];
	
	int i, puissance10, unite;
	for(i=0; i<taille_chaine; i++){
		puissance10 = a/myPow(10, taille_chaine-i-1);
		unite = puissance10 % 10; //Recuperation de l'unite
		result[i] = unite + 48; //48 = 0 en ascii;
	}
	result[taille_chaine] = '\0';
	
	s = result;//Problème de pointeurs HELP !!!!
}
