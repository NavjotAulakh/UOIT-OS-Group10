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
    //Initialize Thread id, proccess array, process status/state and MAX_Ticks
    int proc_status;
    pid_t pid;

    char * const MAX_TICKS ="10";
    char * const argv[] = {"process", MAX_TICKS, 0};
    //Parent Forks to create a child process that executes the signal stop and continue
    pid = fork();
    if (pid == 0){
        execvp("./process", argv);
    }
    //Child process does the intended behaviour for the program and signals
    else{
        sleep(5);
        kill(pid, SIGTSTP);
        sleep(10);
        kill(pid, SIGCONT);
        waitpid(pid, &proc_status, 0);
        return 0;
    }
}