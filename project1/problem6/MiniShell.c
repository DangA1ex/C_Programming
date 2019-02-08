#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void executeCommand(char *command);

int main() {
	char command[9999];
    char commandPrompt[] = "myshell> ";

	// loop endlessly until user inputs exit
	while(1) {
		printf("%s", commandPrompt);

		/* Read command and cut off newline*/
		fgets(command, 9999, stdin);
		command[strlen(command) - 1] = 0;

		// checks for exit command
		if(strcmp(command, "exit") == 0) {
			break;
		}

		executeCommand(command);
	}

	return 0;
}

// checks and executes commands
void executeCommand(char *command) {
	pid_t pid = fork();

    // check if fork failed
    if(pid < 0) {
		perror("fork");
    }

	if(pid == 0) {
		char *args[2];
		args[0] = command;
		args[1] = NULL;

        // checks if execlp failed
		if (execvp(command, args) < 0) {
            printf("ERROR: Command '%s' not found.\n", command);
            exit(1);
        }
	} else {
		wait(NULL);
    }
}