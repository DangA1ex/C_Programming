#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void ChildProcess(void);
void ParentProcess(void);

void main(){
    pid_t pid;
    pid = fork();
    if (pid == 0){
        ChildProcess();
    } else {
        ParentProcess();
    }
}

void ChildProcess(void){
    execl("./MyCompress", "MyCompress", (char *) 0);
}

void ParentProcess(void){
    wait(NULL);
}