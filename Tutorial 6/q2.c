#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(void){
    pid_t pid = 0;
    // Create child process using fork()
    pid = fork();
    
    // Error if unable to fork
    if (pid == -1){
        fprintf(stderr, "Unable to fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // Child process -> sleep for 1 second and print "Child Process"
    else if(pid == 0){
        sleep(1);
        printf("Child Process\n");
        exit(1);
    }
    // Parent process -> wait for child process to terminate using wait() before printing "Parent process".
    else{
        int status;
        if(wait(&status)){
            printf("Parent Process\n");
        }
    }
    return 0;
}
