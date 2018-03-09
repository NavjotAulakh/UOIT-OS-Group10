#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

//Initilize global definitions for constants
#define SIZE 5
#define FILENAME_NUM "numbers.txt"
#define FILENAME_SUM "sum.txt"
sem_t mutex;

int total_sum = 0;
char *write_mode = "w", *read_mode = "r";
int stats;

void *factorial(int dataIn);

int main(void){
    sem_init(&mutex, 0, 1);
    int num[SIZE];

    FILE *fp;

    fp = fopen(FILENAME_NUM, write_mode);

    for (int i = 0; i < SIZE; i++){
        printf("Please enter number %d: ", i + 1);
        scanf("%d", &num[i]);
        fprintf(fp, "%d\n", num[i]);
    }
    fclose(fp);
    
    //Create the child process through fork
    pid_t pid = fork();
    // Initialize the mutex to 1 for an binary semaphore and 0 (2nd param) for local
    sem_init(&mutex, 0, 1);

    //If zero then child process else parent
    if(pid == 0){

        //Initializes the variables, file pointer and threads with size
        int data[SIZE];
        FILE *fp = fopen(FILENAME_NUM, read_mode);
        pthread_t thread[SIZE];

        //Read the file and insert data into the data array
        for (int i = 0; i < SIZE; i++){
            fscanf(fp, "%d \n", &data[i]);
            pthread_create(&thread[i], NULL, (void *(*)(void *)) factorial, (void *)data[i]);
        }
        fclose(fp);

        for(int i = 0; i < SIZE; i++){
            pthread_join(thread[i], NULL);
        }
        sem_destroy(&mutex);

        FILE *f_write = fopen(FILENAME_SUM, write_mode);
        fprintf(f_write, "%d", total_sum);
        fclose(f_write);
        
        return 0;
    }
    else if(pid < 0){
        printf("Forking Error was Generated\n");
        return 0;
    } else {
        //Waits for the child process to finish before continuing
        waitpid(pid, &stats, 0);

        if(stats == 0){
            int sum;
            FILE *f_read = fopen(FILENAME_SUM, read_mode);
            fscanf(f_read, "%d", &sum);
            printf("Sum of all factorials of the five numbers: %d\n", sum);
            fclose(f_read);
        }
    }

    return 0;
}

//Factorial Function
void *factorial(int dataInput){
    int init = 1;
    for(int i=dataInput; i>0; --i){
        init *= i;
    }

    sem_wait(&mutex);
    total_sum += init;
    sem_post(&mutex);

    return 0;
}
