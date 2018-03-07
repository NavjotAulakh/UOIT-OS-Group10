#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

int main(void){
    FILE *file1;
    FILE *file2;

    pid_t pid1 = 0;
    // create first child process
    pid1 = fork();
    
    // error if unable to fork
    if(pid1 == -1){
        fprintf(stderr, "Unable to fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // first child process -> wait 1 second then read the contents of its text file and prints the contents.
    else if(pid1 == 0){
        char read1[256];
        sleep(1);
        file1 = fopen("child1.txt", "r");
        fscanf(file1, "%s", read1);
        printf("%s\n", read1);
        fclose(file1);
        return 0;
    }
    // master process
    else{
        //create second child process
        pid_t pid2 = fork();

        if(pid2 == -1){
            fprintf(stderr, "Unable to fork, error %d\n", errno);
            exit(EXIT_FAILURE);
        }
        // second child process -> wait 1 second then read the contents of its text file and prints the contents.
        else if(pid2 == 0){
            char read2[256];
            sleep(1);
            file2 = fopen("child2.txt", "r");
            fscanf(file2, "%s", read2);
            printf("%s\n", read2);
            fclose(file2);
            return 0;
        }
        // master process -> writes two files 'child1.txt' containing the line Child1 and 'child2.txt' containing the line Child2
        else{
            file1 = fopen("child1.txt", "w");
            file2 = fopen("child2.txt", "w");

            // Print error if either files are NULL
            if (file1 == NULL || file2 == NULL){
                printf("Error opening file\n");
                exit(1);
            }

            const char *text1 = "Child1";
            const char *text2 = "Child2";

            fprintf(file1, "%s", text1);
            fprintf(file2, "%s", text2);
            
            fclose(file1);
            fclose(file2);
        }
    }
    return 0;
}
