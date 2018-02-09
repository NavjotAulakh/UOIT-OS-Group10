#include <stdio.h>
#include <stdlib.h>

struct student{
    char student_id[9];
    int age;
    char year[4];
};

void save_student(struct student a){
    FILE *file;
    file = fopen("students.txt", "a");
    fprintf(file, "%s,%d,%s", a.student_id, a.age, a.year);
    fprintf(file, "\n");
    fclose(file);
};

int main(){
    struct student stud;

    printf("Enter your student id: ");
    scanf("%s", stud.student_id);
    printf("Enter your age: ");
    scanf("%d", &stud.age);
    printf("Enter the year you started at UOIT: ");
    scanf("%s", stud.year);

    save_student(stud);
    return 0;
}
