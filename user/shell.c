#include "libc.c"

#define MAX_COMMAND_LENGTH 20
#define MAX_PARAM_LENGTH 100

void ls();
void cat(char* file);
void rm(char* rm);
void run(char* run);
void help();

int main(int argc, char** argv) {

	char* commandLine[MAX_COMMAND_LENGTH+MAX_PARAM_LENGTH];	// buffer for entire command line
	char* command[MAX_COMMAND_LENGTH];	// buffer for command only
	char* param[MAX_PARAM_LENGTH];		// buffer for params
	
	int length = strlen(commandLine);	// Get command line length
	int gotParams = 0;			// Tells if there is a parameter
	int commandLength;	

	int i;

	while(1) {
		// Read on the command line
		read_string(commandLine);

		// Going through the entire command line
		for(i = 0; i<length;i++) {
			// Search for parameters
			if(commandLine[i] == ' ') 
				gotParams++;

			if(gotParams == 0) {
				// Get commande only
				command[i] = commandLine[i];
			} else {
				// Get the function name length only one time
				if(commandLength == 0)
					commandLength = strlen(command);
				// Get parameter
				param[i-commandLength] = commandLine[i];
			}
		}

		// Call corresponding function
		if(strcmp(command, "help") == 0)
			help();
	
		if(strcmp(command, "ls") == 0)
			ls();

		if(strcmp(command, "cat") == 0)
			cat(param);

		if(strcmp(command, "rm") == 0)
			rm(param);

		if(strcmp(command, "run") == 0)
			run(param);
	}

	exit();
}


// List all files in sfs
void ls() {
	// Iterate through file entries
	int isOk = 0;
	char buf[256];
	while(isOk == 0){
		if(iterator(&isOk, buf) != 0){
			print_string("Iterator fail... aborting");
			break;
		}else
			if(strcomp(buf,"") != 0)
				print_string(buf);	// Display file entry
	} 
}

// Print content of file
void cat(char* file) {
	unsigned char buffer[1024];
	if(read_file(file, buffer) == 0)	// Calls read_file in libc which calls read_file syscall 
		print_string(buffer);
	else
		print_string("Unable to read file");
}

// Removes a file in sfs
void rm(char* rm) {
	if(remove_file(rm) == 0)	// Uses remove_file in libc
		print_string("File successfully removed\n");
	else
		print_string("Unable to remove file");
}

// Execute a user program
void run(char* run) {
	if(exec(run, 0x3000) != 0)	// Put user program at 0x3000 and jump at it
		print_string("Unable to execute file");
}

// Display help
void help() {
	print_string("List of commands\n\r\tls : Display file list\n\r\tcat file : Display file content\n\r\trm file : Remove file\n\r\trun file : Execute file");

}




