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

void intTostr(char* s, int a, int length_str) {
	int taille_chaine = 1; 	

	char result[length_str];
	
	int i, puissance10, unite;
	int nb_numbers = length_str-1;
	for(i=0; i<nb_numbers; i++){
		puissance10 = a/myPow(10, nb_numbers-i-1);
		unite = puissance10 % 10; //Recuperation de l'unite
		result[i] = unite + 48; //48 = 0 en ascii;
	}
	result[length_str-1] = '\0';
	
	for(i=0; i<length_str; i++){
		s[i] = result[i];
	}
}

int lengthInt(int a){
	int length = 1;
	while(a/myPow(10, length) != 0){	
		length++;
	}
	length++;
	return length;
}

/*Exemple
void main(void){
	int test = 1234;
	
	int length_str = lengthInt(test);
	char str[length_str]; //+1 => espace en plus pour le \0
	intTostr(str, test, length_str);
	printf("%s\n", str);
}*/
