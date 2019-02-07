#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void ChildProcess(const char *in, const char *out);
void ParentProcess(const char *in, const char *out);

int main(int argc, char** argv) {
	pid_t pid;
	pid = fork();

	const char *in = argv[1];
	const char *out = argv[2];
    
	if(pid == 0) {
		ChildProcess(in, out);
	}
	else {
		ParentProcess(in, out);
	}
}

void ChildProcess(const char *in, const char *out) {
	printf("Child Process Start\n");
	printf("<-----------------------------------------------------------> \n");
    printf("                _                             \n");
    printf("               | |                             \n");
    printf("__      __ ___ | |  ___  ___   _ __ ___    ___ \n");
    printf("\\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\ \n");
    printf(" \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n");
    printf("  \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n");
    printf("\n");
	printf("CS4440 ForkCompress Program\n");
    printf("Input File: %s \n", in);
    printf("Output File: %s \n", out);
    printf("<-----------------------------------------------------------> \n");
	execl("./MyCompression", " ", in, out, (char*) 0);
}

void ParentProcess(const char *in, const char *out) {
	printf("Parent Process Waiting");
	printf("<-----------------------------------------------------------> \n");
    printf("                _                             \n");
    printf("               | |                             \n");
    printf("__      __ ___ | |  ___  ___   _ __ ___    ___ \n");
    printf("\\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\ \n");
    printf(" \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n");
    printf("  \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n");
    printf("\n");
	printf("CS4440 ForkCompress Program\n");
    printf("Input File: %s \n", in);
    printf("Output File: %s \n", out);
    printf("<-----------------------------------------------------------> \n");
    wait(NULL);
	printf("Child is finished and Parent will now finish");
}
