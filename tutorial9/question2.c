#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

double n = 100000000;
double y[100000000];

double dx = 1 / (n + 1);

double calculateX(double count){
    return count * dx;
}

int main (int argc, char *argv[]){
    
    int nthreads = atoi(argv[1]);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel private(x){
        for (int i=0; i<=n; i++){
            double x = calc(i);
            y[i] = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);
        }
    }


}
