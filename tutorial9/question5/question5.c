// Outputs 0's for x and y for some reason :(

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define n 100000000

double dx = (1/(n+1));

double calcX(int i){
    return i * dx;
}

double calcY(double x){
    return exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
}

int main(int argc, char *argv[]){

    int nthreads = atoi(argv[1]);
    double x;
    double y;

    FILE *fp;
    fp = fopen("calculation.txt", "w");

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel private(x)
    for(int i = 0; i <= n; i++){
        x = calcX(i);
        y = calcY(x);
        #pragma omp critical
        {
            #ifdef _OPENMP
                if(i % 1000000 == 0){
                    fprintf(fp, "Calculation: %d, x = %f, y = %f\n", i,x,y);
                }
            #endif
        }
    }
    fclose(fp);
}
