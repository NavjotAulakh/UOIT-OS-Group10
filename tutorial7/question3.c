#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    //Initialize Thread id, proccess array
    pid_t pid;
    char * const argv[] = {"process", NULL};

    //Parent Forks to create a child process that executes the signal stop
    pid = fork();
    if (pid == 0){
        execvp("./process", argv);
    }
    //Child process does the intended behaviour for the program and signals
    else{
        sleep(5);
        kill(pid, SIGINT);
        return 0;
    }
}