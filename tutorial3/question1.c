#include <stdlib.h>
#include <stdio.h>
int main(void)
    {
        char firstName[12], age[3], weight[4];
        
        printf("Please Enter your First Name: \n");
        scanf("%s", firstName);
        printf("Please Enter your Age (in years): \n");
        scanf("%s", age);
        printf("Please Enter your Weight (in lbs): \n");
        scanf("%s", weight);

        printf("Your First Name is %s.\nYour Age is %s.\nYour Weight is %s.\n",firstName,age,weight);
    }