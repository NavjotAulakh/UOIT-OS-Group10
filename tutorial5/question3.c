#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct students{
    char name[256];
    int student_id;
    float grade;
};

// Void with pointer to take in any type of input
// for the class_total function and entrypoints for threads.
void* bellcurve(void *args)
{
    struct students student;

    student = *(struct students *)args;
    student.grade = student.grade * 1.5;
    printf("The Bellcurved Student: %s, %d, %f\n", student.name, student.student_id, student.grade);
    pthread_exit(NULL);
}

int main()
{
    // Prompts the professor for the grades
    struct students record[5];

    printf("Please enter the students name, id and grade. (Input Format: Name ID Grade)\n");
    scanf("%s %d %f", record[0].name, &record[0].student_id, &record[0].grade);
     printf("Please enter the students name, id and grade. (Input Format: Name ID Grade)\n");
    scanf("%s %d %f", record[1].name, &record[1].student_id, &record[1].grade);
     printf("Please enter the students name, id and grade. (Input Format: Name ID Grade)\n");
    scanf("%s %d %f", record[2].name, &record[2].student_id, &record[2].grade);
     printf("Please enter the students name, id and grade. (Input Format: Name ID Grade)\n");
    scanf("%s %d %f", record[3].name, &record[3].student_id, &record[3].grade);
     printf("Please enter the students name, id and grade. (Input Format: Name ID Grade)\n");
    scanf("%s %d %f", record[4].name, &record[4].student_id, &record[4].grade);

    // Creates the five threads and then executes them
    pthread_t thr1, thr2, thr3, thr4, thr5;

    if(pthread_create(&thr1, NULL, &bellcurve, (void*)&record[0]))
    {
        printf("This thread could not be created!\n");
        return -1;
    }
    if(pthread_create(&thr2, NULL, &bellcurve, (void*)&record[1]))
    {
        printf("This thread could not be created!\n");
        return -1;
    }
    if(pthread_create(&thr3, NULL, &bellcurve, (void*)&record[2]))
    {
        printf("This thread could not be created!\n");
        return -1;
    }
    if(pthread_create(&thr4, NULL, &bellcurve, (void*)&record[3]))
    {
        printf("This thread could not be created!\n");
        return -1;
    }
    if(pthread_create(&thr5, NULL, &bellcurve, (void*)&record[4]))
    {
        printf("This thread could not be created!\n");
        return -1;
    }
   

    // Waits for all of the threads to join
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);
    pthread_join(thr4, NULL);
    pthread_join(thr5, NULL);

    return 0;
}
