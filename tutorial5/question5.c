#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define THREAD_COUNT 10

//Initialize global variables
float total_grade;
float total_bellcurve;
struct students{
    float grade;
};
//Create a barrier when reading file
pthread_barrier_t mybarrier;
// Create a mutex this ready to be locked!
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// bellcurve function and entrypoint for threads.
void* save_bellcurve(void *grade)
{
    pthread_barrier_wait(&mybarrier);
    pthread_mutex_lock(&m);

    //Initialize file to write
    FILE * fp;

    fp = fopen ("bellcurve.txt", "a");
	struct students student;
	student = *(struct students *)grade;

    total_grade += student.grade;
	total_bellcurve += student.grade * 1.5;

 	fprintf(fp, "Bellcurved Grade: %f\n", student.grade * 1.5);
    fclose(fp);
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

struct students values[10];

void* read_grades(){

    // Initializing the file pointer
	FILE *fs;
 
	char ch, buffer[32];
	int i = 0, j = 0;
	
	// Openning the file with file handler as fs
	fs = fopen("grades.txt", "r");
    
	// Read the file unless the file encounters an EOF
	while(1){

		// Reads the character where the seeker is currently
		ch = fgetc(fs);

		// If EOF is encountered then break out of the while loop
		if(ch == EOF){
            //Stores the last number in the file before closing
            values[j].grade = atoi(buffer);
            printf("%f\n",values[j].grade);
            fclose(fs);
            pthread_barrier_wait(&mybarrier);
			break;
		}
 
		// If the delimiter is encounterd store the last read char array into an int
		else if(ch == ',' || ch == '\n' ){
 
			// Converting the content of the buffer into an array position
			values[j].grade = atoi(buffer);
            
			// Increamenting the array position
			j++;
 
			// Clear the buffer
			memset(buffer, 32, 0);
 
			// clear the counter that counts the number
			i = 0;
 
			continue;
		}
		else{
 
			// reads the current character in the buffer
			buffer[i] = ch;
			i++;
		}
	}
}
// Inputs the grades.txt file to the students struct
int main () {

//Initialize barrier
pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT + 1);

//Initialize the 10 requred threads
pthread_t thr0, thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8, thr9, thr10;
    if(pthread_create(&thr0, NULL, &read_grades, NULL))
    {
        printf("This thread could not be created!\n");
    }
    
	if(pthread_create(&thr1, NULL, &save_bellcurve, (void*)&values[0].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr2, NULL, &save_bellcurve, (void*)&values[1].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr3, NULL, &save_bellcurve, (void*)&values[2].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr4, NULL, &save_bellcurve, (void*)&values[3].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr5, NULL, &save_bellcurve, (void*)&values[4].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr6, NULL, &save_bellcurve, (void*)&values[5].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr7, NULL, &save_bellcurve, (void*)&values[6].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    
	if(pthread_create(&thr8, NULL, &save_bellcurve, (void*)&values[7].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
 	if(pthread_create(&thr9, NULL, &save_bellcurve, (void*)&values[8].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
 	if(pthread_create(&thr10, NULL, &save_bellcurve, (void*)&values[9].grade))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}

//Waits for all ten threads to complete
pthread_join(thr1, NULL);
pthread_join(thr2, NULL);
pthread_join(thr3, NULL);
pthread_join(thr4, NULL);
pthread_join(thr5, NULL);
pthread_join(thr6, NULL);
pthread_join(thr7, NULL);
pthread_join(thr8, NULL);
pthread_join(thr9, NULL);
pthread_join(thr10,NULL);

printf("Average Grade of the students: %f\nAverage Bellcurved grade of the students: %f\n", total_grade/10,total_bellcurve/10);
return 0;
}
