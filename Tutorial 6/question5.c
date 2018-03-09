#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>

//size of the array
#define SIZE 5
#define FILENAME_NUM "numbers.txt"
#define FILENAME_SUM "sum.txt"
sem_t mutex;

int total_sum = 0;
char *mode_w = "w", *mode_r = "r";
int stat;

void *factorial(int dataIn);

int main(void){
    pthread_t thread[SIZE];
    sem_init(&mutex, 0, 1);
    int num[SIZE];

    FILE *fp;

    fp = fopen(FILENAME_NUM, mode_w);

    for (int i = 0; i < SIZE; i++){
        printf("Enter number %d: ", i + 1);
        scanf("%d", &num[i]);
        fprintf(fp, "%d\n", num[i]);
    }
    fclose(fp);
    
    //make child process
    pid_t pid = fork();

    sem_init(&mutex, 0, 1);

    //child process
    if(pid == 0){
        int data[SIZE];
        FILE *fp = fopen(FILENAME_NUM, mode_r);

        pthread_t thread[SIZE];
        for (int i = 0; i < SIZE; i++){
            fscanf(fp, "%d \n", &data[i]);
            pthread_create(&thread[i], NULL, (void *(*)(void *)) factorial, (int *) data[i]);
        }
        fclose(fp);

        for(int i = 0; i < SIZE; i++){
            pthread_join(thread[i], NULL);
        }
        sem_destroy(&mutex);

        FILE *fp3 = fopen(FILENAME_SUM, mode_w);
        fprintf(fp3, "%d", total_sum);
        fclose(fp3);
        
        return 0;
    }
    else if(pid < 0){
        printf("Forking error \n");
        return 0;
    }
    //parent process
    else{
  //wait for child process to finish
        waitpid(pid, &stat, 0);

        if(stat == 0){
            int sum;
            FILE *fp1 = fopen(FILENAME_SUM, mode_r);
            fscanf(fp1, "%d", &sum);
            printf("Sum of all factorials of the five numbers: %d\n", sum);
            fclose(fp1);
        }
    }

    return 0;
}

//factorial function
void *factorial(int dataIn){
    int init = 1;

    for(int i=dataIn; i>0; --i){
        init *= i;
    }

    sem_wait(&mutex);
    total_sum += init;
    sem_post(&mutex);

    return 0;
}
