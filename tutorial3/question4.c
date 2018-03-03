#include <stdio.h>
#include <stdlib.h>

int main(){
    char *professor;
    int *student_ids, *grades;
    int number_of_students;

    professor = (char *)calloc(256, sizeof(char));

    printf("Enter your name: ");
    scanf("%s", professor);
    printf("Enter number of students to mark: ");
    scanf("%d", &number_of_students);

    student_ids = (int *)malloc(number_of_students * sizeof(int));
    grades = (int *)malloc(number_of_students * sizeof(int));

    free(professor);
    free(student_ids);
    free(grades);
    return 0;
}
