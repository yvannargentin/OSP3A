#include "libc.h"

#define MAX_COMMANDE_LENGTH 20
#define MAX_PARAM_LENGTH 100


int main(int argc, char** argv) {

	char* commandeLine[MAX_COMMANDE_LENGTH+MAX_PARAM_LENGTH];
	char* commande[MAX_COMMANDE_LENGTH];
	char* param[MAX_PARAM_LENGTH];


	while(1) {
		// Read on the commande line
		read_string(commandeLine);

		int length = strlen(commandeLine);
		int gotParams = 0;
		int commandeLength;

		for(int i = 0; i<strlen;i++) {
			// Search for parameters
			if(commandeLine[i] == ' ') 
				gotParams++;

			if(gotParams == 0) {
				// Get commande only
				commande[i] = commandeLine[i];
			} else {
				if(commandeLength == 0)
					commandeLength = strlen(commande);
				// Get parameter
				param[i-commandeLength] = commandeLine[i];
			}
		}

		// Call corresponding function
		if(strcmp(commande, "help") == 0)
			help();
	
		if(strcmp(commande, "ls") == 0)
			ls();

		if(strcmp(commande, "cat") == 0)
			cat(param);

		if(strcmp(commande, "rm") == 0)
			rm(param);

		if(strcmp(commande, "run") == 0)
			run(param);
	}
}



void ls() {
}

void cat(char* file) {
}

void rm(char* rm) {
}

void run(char* run) {
}

void help() {
	print_string("List of commands\n\r\tls : Display file list\n\r\tcat file : Display file content\n\r\trm file : Remove file\n\r\trun file : Execute file");

}




