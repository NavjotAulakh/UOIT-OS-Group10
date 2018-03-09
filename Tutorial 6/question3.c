#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

//Define the constant size of the array
#define SIZE 5

sem_t mutex; //Declares the Semaphore

//Initialize global array and set it to zeros
int moving_sum[5] = {0};

//Structure for the data
typedef struct{
    int number;
    int index;
} data;

//Declare Factorial Fucntion
void *factorial(void *data);

int main(void){
    //Initilize variables and threads
    int num[SIZE];
    pthread_t thread[SIZE];

    // Initialize the mutex to 1 for an binary semaphore and 0 (2nd param) for local
    sem_init(&mutex, 0, 1);
    data collect[SIZE];

    printf("Please input five numbers(integers): \n");
    for(int i=0; i<SIZE; i++){
        //Prompt the user to input five integers
        printf("Please enter number %d: ", i+1);
        scanf("%d", &num[i]);
        collect[i].number = num[i];
        collect[i].index = i;

        //Initialize the pthread and call the factorial
        pthread_create(&thread[i], NULL, factorial, (void *)&collect[i]);
    }

    for(int i=0; i<SIZE; i++){
        pthread_join(thread[i], NULL);
    }

    //Print the moving summation content
    printf("\nMoving summation for the five integers is \n\n");
    for(int i=0; i<SIZE; i++){
        printf("Moving Sum with Number %d %10d \n", (i+1),moving_sum[i]);
    }
    sem_destroy(&mutex);
}

//Factorial Function
void *factorial(void *values){
    data param = *(data *) values;

    //Retreive the factorial from the function
    int factorial = compute_the_factorial(param.number);

    if(param.index == 0){
        moving_sum[0] = factorial;
    }
    else{
        sem_wait(&mutex);
        while(moving_sum[param.index-1] == 0){
            sem_post(&mutex); 
            sem_wait(&mutex);
        }
        moving_sum[param.index] = moving_sum[param.index - 1] + factorial;
        sem_post(&mutex);
    }
    return NULL;
}

// Function to compute the factorial for each input integers
int compute_the_factorial(int integer){
    if(integer <= 1){
        return 1;
    } else {
        return (integer * compute_the_factorial(integer - 1));
    }
}