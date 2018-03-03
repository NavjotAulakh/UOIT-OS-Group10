#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 

int main() {
	pthread_t 1stthread, 2ndthread;
	
	
	if (pthread_create(&1stthread, NULL, &hello_world, NULL)) {
		printf("this thread could not be created 1\n");
		return -1;
	}
	
	if (pthread_create(&2ndthread, NULL, &goodbye, NULL)) {
		printf("this thread could not be created 2\n");
		return -1;
	}

	
	if (pthread_join(1stthread, NULL)) {
		printf("this thread could not be joined 1\n");
		return -1;
	}
	
	if (pthread_join(2ndthread, NULL)) {
		printf("this thread could not be joined 2\n");
		return -1;
	}

	return 0;
}
void *hello_world() {
	srand(time(NULL));
	sleep(rand() % 8);
	printf("hello world\n");
	return NULL;
}

void *goodbye() {
	srand(time(NULL));
	sleep(rand() % 3);
	printf("goodbye\n");
	return NULL;
}