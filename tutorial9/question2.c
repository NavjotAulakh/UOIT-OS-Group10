#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]){
    //ask for user input to specify the number of threads
    if(argc != 2){
        printf("Please enter only one argument, the number of threads.\n");
        return 1;
    }
	
    int value = 0;
    int thread_num, numOfThreads = atoi(argv[1]);
    #ifdef _OPENMP
    omp_set_num_threads(numOfThreads);
    #endif

    //assign n
    int n = 10000000;

    //array y containing 100 million double values
    double y[n];
    double dx, x;
    dx = (double) 1 / (n + 1);

    #pragma omp parallel
    {
        #pragma omp critical
        {
            #ifdef _OPENMP
            value += 1; // THREAD SAFE INCREMENT
            thread_num = omp_get_thread_num();
            printf("Thread Number = %d, Value = %d\n", thread_num, value);
        
            for (int i = 0; i < n; i++){
                x = i * dx;
                y[i] = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0); 
                printf("%f \n", y[i]);
            }
            #endif
        }
    }
    return 0;
}
