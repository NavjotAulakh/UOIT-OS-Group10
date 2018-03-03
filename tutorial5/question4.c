#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//Initialize global variables
float totalGrade;

// Create a mutex this ready to be locked!
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

// Void with pointer to take in any type of input
// for the class_total function and entrypoints for threads.
void* class_total(void *args)
{
	pthread_mutex_lock(&m);

	float grade;
	grade = *(float *)args;
    totalGrade += grade;
	printf("Total grade: %f\n", totalGrade);

	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
}

int main()
{
	// Prompt the user to enter 10 grades.
	float grade1, grade2, grade3, grade4, grade5, grade6, grade7, grade8, grade9, grade10;
	printf("Enter a grade:\n");
	scanf("%f", &grade1);
	printf("Enter a grade:\n");
	scanf("%f", &grade2);
	printf("Enter a grade:\n");
	scanf("%f", &grade3);
	printf("Enter a grade:\n");
	scanf("%f", &grade4);
	printf("Enter a grade:\n");
	scanf("%f", &grade5);
	printf("Enter a grade:\n");
	scanf("%f", &grade6);
    printf("Enter a grade:\n");
	scanf("%f", &grade7);
    printf("Enter a grade:\n");
	scanf("%f", &grade8);
    printf("Enter a grade:\n");
	scanf("%f", &grade9);
    printf("Enter a grade:\n");
	scanf("%f", &grade10);

	// Create 10 threads and execute them.
	pthread_t thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8, thr9, thr10;
	if(pthread_create(&thr1, NULL, &class_total, (void*)&grade1))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr2, NULL, &class_total, (void*)&grade2))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr3, NULL, &class_total, (void*)&grade3))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr4, NULL, &class_total, (void*)&grade4))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
	if(pthread_create(&thr5, NULL, &class_total, (void*)&grade5))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    if(pthread_create(&thr6, NULL, &class_total, (void*)&grade6))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    if(pthread_create(&thr7, NULL, &class_total, (void*)&grade7))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    if(pthread_create(&thr8, NULL, &class_total, (void*)&grade8))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    if(pthread_create(&thr9, NULL, &class_total, (void*)&grade9))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}
    if(pthread_create(&thr10, NULL, &class_total, (void*)&grade10))
	{
    	printf("This thread could not be created!\n");
    	return -1;
	}

	// Wait for the threads to finish.
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	pthread_join(thr3, NULL);
	pthread_join(thr4, NULL);
	pthread_join(thr5, NULL);
    pthread_join(thr6, NULL);
	pthread_join(thr7, NULL);
	pthread_join(thr8, NULL);
	pthread_join(thr9, NULL);
	pthread_join(thr10, NULL);

	return 0;
}

