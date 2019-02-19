#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void processCommand(char *command, char **parts);
void executeCommand(char **parts);

int main() {
	char command[9999];
    char commandPrompt[] = "shell> ";
	char *commandParts[99];

	printf("--------------------------------------------------------------------------------\n");
	printf("    ██████╗ ██╗   ██╗██████╗       ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("    ██╔══██╗██║   ██║██╔══██╗      ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("    ██║  ██║██║   ██║██████╔╝█████╗███████╗███████║█████╗  ██║     ██║     \n");
	printf("    ██║  ██║██║   ██║██╔═══╝ ╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("    ██████╔╝╚██████╔╝██║           ███████║██║  ██║███████╗███████╗███████╗\n");
	printf("    ╚═════╝  ╚═════╝ ╚═╝           ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Shell that takes commands with or without arguments, uses dup2() and pipe().\n");
	printf("--------------------------------------------------------------------------------\n");


	// loop endlessly until user inputs exit
	while(1) {
		printf("%s", commandPrompt);

		fgets(command, 9999, stdin);
		
		// removes newline from input
        command[strcspn(command, "\n")] = '\0';

		// checks if empty string was entered
		if(strlen(command) == 1) {
			continue;
		}

		processCommand(command, commandParts);

		// exits if command was entered
		if(strcmp(command, "exit") == 0) {
			break;
		}

		executeCommand(commandParts);
	}

	return 0;
}

void processCommand(char *command, char **parts) {
	parts[0] = strtok(command, " ");
    int i = 0;

	// goes through command seperating by ' ' and adds to parts
    while (parts[i] != NULL) {
      i++;
      parts[i] = strtok(NULL, " ");
    }
	
	// terminates parts array
	parts[i++] = "\0";
}

void executeCommand(char **parts) {
	char *newParts[99] = {NULL};
	int pipeLoc = 0;
	int fd[2];

	// checks for empty command
	for(int i = 0; i < 99; i++) {
		if(strlen(parts[i]) == 0) {
			// if first part is empty, break out of loop
			if(i == 0) {
				return;
			}
			break;
		} else if(strcmp(parts[i], "|") == 0) {
			// checks pipe location and outputs error if error occurs
			if(i == 0) {
				printf("ERROR: Syntax error.\n");
				return ;
			}

			if(pipeLoc > 0) {
				printf("ERROR: Only one pipe supported!\n");
				return ;
			}

			if(strlen(parts[i+1]) == 0) {
				printf("ERROR: Syntax error.\n");
				return ;
			}

			// saves the location of the pipe
			pipeLoc = i;

			// adds NULL to where the pipe is
			newParts[i] = NULL;
		} else {
			newParts[i] = parts[i];
		}
	}

	// Create a pipe if needed
	if(pipeLoc > 0) {
		if(pipe(fd)) {
			printf("ERROR: pipe() failed!\n");
			return ;
		}
	}

	pid_t pid = fork();

	// checks if fork successful
	if(pid < 0) {
		printf("ERROR: fork() failed.\n");
	}

	if(pid == 0) {
		// redirects output if pipe is found
		if(pipeLoc > 0) {
			close(fd[0]);
			close(STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		
		if (execvp(newParts[0], newParts) < 0) {
            printf("ERROR: Command %s not found.\n", newParts[0]);
            exit(1);
        }
	} else {
		// create another child since pipe was found
		if(pipeLoc > 0) {
			pid_t pid2 = fork();

			if(pid2 < 0) {
				printf("ERROR: Second fork() failed.\n");
				wait(NULL);
			}

			if(pid2 == 0) {
				// redirects the input
				close(fd[1]);
				close(STDIN_FILENO);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);

				if (execvp(newParts[pipeLoc+1], newParts+pipeLoc+1) < 0) {
            		printf("ERROR: Command %s not found.\n", newParts[pipeLoc+1]);
        		    exit(1);
        		}
			} else {
				close(fd[0]);
				close(fd[1]);

				// waits for both children to finish
				wait(NULL);
				wait(NULL);
			}
		} else {
			// if only one child then wait for it to finish
			wait(NULL);
		}
	}
}