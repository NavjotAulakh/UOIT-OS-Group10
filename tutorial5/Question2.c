#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 #define COUNT 5


struct students{
   
float grade;
};
    
 void* bellcurve(void *args){
     struct students person;
     person = *(struct students *)args;
     person.grade = person.grade * 1.5;
     printf("The Bellcurved grade: %f\n", person.grade);
     pthread_exit(NULL);
 }
 
   int main(){
       int grades[COUNT];
       pthread_t threads[COUNT];

       int i;
       for (i=0;i<COUNT;i++){
		printf("Type in grade %d: ", i);
		scanf("%d", &grades[i]);
}
for (i=0; i<COUNT; i++) {
		if (pthread_create(&threads[i], NULL, &bellcurve, &grades[i])) {
			printf("thread could not be created  %d\n", i);
			return -1;
}
for (i=0; i<COUNT; i++) {
		if (pthread_join(threads[i], NULL)) {
			printf("Thread could not be joined %d\n", i);
			return -1;
}
return 0
   }
     