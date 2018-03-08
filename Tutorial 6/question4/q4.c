#define _XOPEN_SOURCE 700
#define NUMBERS 10

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <time.h>

// global array buffer of length 5, shared by prodicer and customers
int buffer[5] = {0};
int numbers[NUMBERS];
sem_t sem;

void *producer(int numbers[]){
    // initialize random integet to represent sleep time (0-5)
    srand(time(NULL));
    int rand_time = rand()%6;
    
    int buffer_used = 0; // counter for number of buffer spots used
    int count = 0; // counter for the loop
    // while loop will run as long as the counter is less than NUMBERS
    while(count < NUMBERS){
        sleep(rand_time); // random delay
        // if buffer is not currently full
        if(buffer_used <= 5){
            sem_wait(&sem); // lock thread
            //  if current spot is not used
            if(buffer[buffer_used] == 0){
                printf("Produced %d\n", numbers[count]); // print to indicate number that has been added to the buffer
                buffer[buffer_used] = numbers[count]; // use spot in buffer
                count++; // increment count
            }
            // incremnt if buffer is used
            else{
             buffer_used++;
            }
            sem_post(&sem); // unlock thread
        }
        // reset counter if buffer is full
        else{
         buffer_used = 0;
        }
    }
    return 0;
}

void *consumer(){
    // initialize random integet to represent sleep time (0-5)
    srand(time(NULL));
    int rand_time = rand()%6;
    
    int buffer_used = 0; // counter for number of buffer spots used
    int count = 0; // counter for the loop
    // while loop will run as long as the counter is less than NUMBERS
    while (count < NUMBERS){
        sleep(rand_time); // random delay
        // if buffer is not currently full
        if(buffer_used <= 5){
            sem_wait(&sem); // lock thread
            // if the current spot is used
            if(buffer[buffer_used] != 0){
                printf("Consumed %d\n", buffer[buffer_used]); // print to indicate number that has been consumed from the buffer
                buffer[buffer_used] = 0; // 
                count++; // increment count
            }
            // increment if buffer is not used
            else{
                buffer_used++;
            }
            sem_post(&sem); // unlock thread
        }
        // reset counter if buffer is full
        else{
            buffer_used = 0;
        }
    }
}

int main(void){
    pthread_t threads[2]; // initialize threads array
    sem_init(&sem, 0, 1); // initialize semaphore
    printf("Please enter 10 numbers: \n"); // prompt user for 10 numbers

    // take number inputs
    for(int i = 0; i < 10; i++){
        scanf("%d", &numbers[i]);
    }
    // create consumer and producer threads
    for(int i = 0; i < 2; i++){
        if(i == 0){
            pthread_create(&threads[i], 0, producer, (int *)numbers);
        }
        else{
            pthread_create(&threads[i], 0, consumer, (void *)NULL);
        }
    }

    sem_destroy(&sem); // remove semaphore

    // wait for both threads to finish
    for (int i = 0; i < 2; i++){
        pthread_join(threads[i], NULL);
    }

    // print the contents of the buffer
    for(int i = 0; i < 5; i++){
        printf("%d\n", buffer[i]);
    }
}
