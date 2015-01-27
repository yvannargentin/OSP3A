/*
\file exec.c
\brief this file content the exec fonction
*/
#include "nomenclature.h"

/*
This fonction read the file, put it in memory and jump to the segment
\param filename the name of the file to read
\param seg were we put the binary file
\return return 0 if succeed and -1 if failure
*/
int execute(char *filename, uint seg){
	unsigned char *contenu;
	int i;
	stat_st stats;
	int length_str;
	char str[5]; // to print the size

        //load binary image in memory (adress X)
	if (read_file(filename, contenu) != 0)  // read the content of the file
		print_string("erreur read_file");
	else{
		// print the length that we should read
		print_string("bytes to read");
		if(get_stat(filename,&stats) != 0)
			print_string("erreur get_stat");
		
		if (lengthStr(contenu) == 0)
			return 1;
		else {
			// print the length that we read
			print_string("bytes readed");
			length_str = lengthInt(lengthStr(contenu));
			intTostr(str, lengthStr(contenu), length_str);
			print_string(str);

			// print what we read and copy image from X in seg
			for(i=0; i< lengthStr(contenu); i++){
				print_char(contenu[i]);
				memputb(seg, i*8, contenu[i]);
			}

			print_string("after memputb, now we jump");
			jump(seg); // jump to seg
			
			return 0;
		}
	}
}
