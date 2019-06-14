#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void executeCommand(char **args);
void processCommand(char *command, char **args);

int main() {
	char command[999];
    char *args[99] = {};
    char commandPrompt[] = "shell> ";

	printf("--------------------------------------------------------------------------------\n");
	printf("███╗   ███╗ ██████╗ ██████╗ ███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██╔═══██╗██╔══██╗██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║   ██║██████╔╝█████╗█████╗███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║   ██║██╔══██╗██╔══╝╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║╚██████╔╝██║  ██║███████╗    ███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Shell that takes commands with or without arguments.\n");
	printf("--------------------------------------------------------------------------------\n");

	// loop endlessly until user inputs exit
	while(1) {
		printf("%s", commandPrompt);
        fgets(command, 9999, stdin);

		// removes newline from input
        command[strcspn(command, "\n")] = '\0';

		// checks if empty string was entered
        if (strlen(command) == 1) {
		    continue;
	    }

        processCommand(command, args);

		// checks if exit was entered, if so ends program
        if (strcmp(command, "exit") == 0) {
            break;
        }

        executeCommand(args);
	}

	return 0;
}

void processCommand(char *command, char **args) {
	args[0] = strtok(command, " ");
    int i = 0;

	// goes through command seperating by ' ' and adds to args
    while (args[i] != NULL)
    {
      i++;
      args[i] = strtok(NULL, " ");
    }
}

// checks and executes commands
void executeCommand(char **args) {
	pid_t pid = fork();

	// checks if fork successful
	if(pid < 0) {
		printf("ERROR: fork() failed.\n");
	}

	if(pid == 0) {
		if (execvp(args[0], args) < 0) {
            printf("ERROR: Command not found.\n");
            exit(1);
        }
	} else {
		wait(NULL);
	}
}