#include "libc.c"

#define MAX_COMMANDE_LENGTH 20
#define MAX_PARAM_LENGTH 100

void ls();
void cat(char* file);
void rm(char* rm);
void run(char* run);
void help();

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

		int i;
		for(i = 0; i<length;i++) {
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

	exit();
}



void ls() {
	
}

void cat(char* file) {
	unsigned char buffer[1024];
	if(read_file(file, buffer) == 0) 
		print_string(buffer);
	else
		print_string("Unable to read file");
}

void rm(char* rm) {
	if(remove_file(rm) == 0)
		print_string("File successfully removed\n");
	else
		print_string("Unable to remove file");
}

void run(char* run) {
	if(exec(run, 0x3000) != 0)
		print_string("Unable to execute file");
}

void help() {
	print_string("List of commands\n\r\tls : Display file list\n\r\tcat file : Display file content\n\r\trm file : Remove file\n\r\trun file : Execute file");

}




