/* Tutorial 3 Question 1 
**Group 5
**By: Carlos Fabregas
** Prompts the user for their first name, age and height then prints it back into console
*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char name[20];
    int age;
    int height;

    //asks for user input
    printf("What is your first name? \n");
    scanf("%s", &name);

    printf("What is your age? \n");
    scanf("%d", &age);

    printf("What is your height? \n");
    scanf("%d", &height);
    //prints out user input to terminal
    printf("Your first name is %s, your age is %d and your height is %d \n", name, age, height);
    


}