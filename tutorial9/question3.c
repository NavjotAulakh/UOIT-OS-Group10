#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define MAX_ARR_LENGTH  1000000

int randomInteger(int min_int, int max_int) {
	int result = 0, low_int = 0, high_int = 0;

	if (min_int < max_int) {
		low_int = min_int;
		high_int = max_int + 1; // include maximum integer in output
	} else {
		low_int = max_int + 1; // include maximum integer in output
		high_int = min_int;
	}

	srand(time(NULL));
	result = (rand() % (high_int - low_int)) + low_int;
	return result;
}

int main() {
	int x[MAX_ARR_LENGTH];
	int norm;
	
	double serialStartTime = omp_get_wtime();
	for(int i = 0; i < MAX_ARR_LENGTH; i++) {		
		x[i] = rand() % 101;
		norm += fabs(x[i]);
	}
	double serialWallTime = omp_get_wtime() - serialStartTime;	

	double parallelStartTime = omp_get_wtime();
	#pragma omp parallel for reduction(+:norm)
	for (int i =0; i < MAX_ARR_LENGTH; i++) {
		norm += fabs(x[i]);
	}
	double parallelWallTime = omp_get_wtime() - parallelStartTime;

	printf("Total Wall Time for Serial: %f\nTotal Wall Time for Parallel: %f\n", serialWallTime, parallelWallTime);
}
