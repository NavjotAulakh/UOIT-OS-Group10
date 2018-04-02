#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(void){
	//initialize constants
	const int WIDTH = 100;
	const int HEIGHT = 100;
	
	//initialize 2D arrays
	int a[WIDTH][HEIGHT];
	int b[WIDTH][HEIGHT];
	int finalMatrix[WIDTH][HEIGHT];

	int i, j, k;

	//fill array a
	for ( i = 0; i < WIDTH; i++) {
		for ( j = 0; j < HEIGHT; j++) {
			a[i][j] = j;
		}
	}
	
	//fill array b
	for ( i = 0; i < WIDTH; i++) {
		for ( j = 0; j < HEIGHT; j++) {
			b[i][j] = j;
		}
	}

	//matrix multiplication
	#pragma omp parallel shared(a, b, finalMatrix) private(i, j, k)
	{
		#pragma omp for schedule(static)
		for ( i = 0; i < WIDTH; i++) {
			for ( j = 0; j < HEIGHT; j++) {
				for ( k = 0; k < WIDTH; k++) {
					finalMatrix[i][j] = a[i][k] + b[k][j];
				}
			}
		}
	}
	
	//print out the final matrix
	for ( i = 0; i < WIDTH; i++) {
		for ( j = 0; j < HEIGHT; j++) {
			printf("%d ", finalMatrix[i][j]);
			if(j == HEIGHT - 1)
				printf("\n\n");
		}
	}

	return 0;
}
