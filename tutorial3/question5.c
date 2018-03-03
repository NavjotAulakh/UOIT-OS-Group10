#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct grade
{
	int student_id;
	int mark;
};

void grade_students(struct grade *grades, int num_students)
{
	int sum, stud_count;
	FILE* file;
	double mean;
	double stdev;
	sum = 0;
	stud_count = 0;
	stdev = 0.0f;
	file = fopen("grades.txt", "w");

	while (num_students > stud_count)
	{
		sum += grades[stud_count].mark;
		fprintf(file, "%d Student ID: %d & Mark: %d \n", (stud_count + 1), grades[stud_count].student_id, grades[stud_count].mark);
		stud_count++;
	}
	
	mean = (float)sum / num_students;
	stud_count = 0;
	while (num_students > stud_count)
	{
		stdev += pow((grades[stud_count].mark - mean), 2);
		stud_count++;
	}
	stdev = sqrt(stdev / num_students);
	fprintf(file, "Mean is %f & Standard Deviation is %f", mean, stdev);

	fclose(file);
};

int main()
{
	//Initializes the variables
	char* professor;
	char c;
	int num_students;
	int stud_count;
	struct grade* grades;
	
	stud_count = 0;
	num_students = 0;
	professor = (char*)calloc(256, sizeof(char));
	
	//Prompts the user for prof's name
	printf("Enter professor's name: \n");
	fgets(professor, 256, stdin);
	
	//Prints the number of students
	printf("Enter the number of students: \n");
	while ((c = fgetc(stdin)) != '\n' ) {
		num_students = num_students * 10 + (c - '0');
	}

	grades = malloc(sizeof(struct grade)*num_students);
	while (stud_count < num_students) 
	{
		grades[stud_count].mark = 0; grades[stud_count].student_id = 0;
		printf("Please enter the student's ID: ");
		while ((c = fgetc(stdin)) != '\n') {
			grades[stud_count].student_id = grades[stud_count].student_id * 10 + (c - '0');

		}
		printf("Please enter the student's mark: ");
		while ((c = fgetc(stdin)) != '\n') {
			grades[stud_count].mark = grades[stud_count].mark * 10 + (c - '0');

		}
		stud_count++;
	}
	//Grades the entered marks for all students
	grade_students(grades, num_students);
	//Frees the memory after use
	free(grades);
	free(professor);
	return 0;
}
