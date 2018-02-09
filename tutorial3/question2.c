/*Tutorial 3Question 2
**Group 5
**By: Carlos Fabregas
** Reads a file for integers, stores them into an array and outputs the values into terminal
*/
#include <stdio.h>
#include <stdlib.h>


int main(){
    int c;
    FILE *file;
    int num[10];

    file = fopen("question2.txt", "r");

    //checks if file excist
    if(file == NULL){
        printf("Error Opening File");
        
        exit(1);
    }
    else{
        int i=0;
        //reads number by number until the end of the file
        while(!feof(file)){
            
            fscanf(file,"%d", &num[i]);
            i++;
        }
        //prints out numbers stored in the array
        for(int j=0; j < i-1; j++){
            printf("%d \n" , num[j]);
        }

        fclose(file);
    }

    
}