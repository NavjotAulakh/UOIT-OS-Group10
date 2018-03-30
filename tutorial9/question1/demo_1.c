#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    printf("This statement will always print.\n");
    // Uses OpenMP library to print the statement in parallel with the above print statement when '-fopenmp' is used when compiled
    #ifdef _OPENMP
    printf("This statement will only print when compiled with \"-fopenmp\"\n");
    #endif
    return 0;
}
