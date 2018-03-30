#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
    // identifies the number of threads to create (16) when compiled using OpenMP
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    // forks additional threads
    #pragma omp parallel
    {
        // omp critical instructs code to run section to be executed by a single thread at a time
        #pragma omp critical
        {
            thread_num = omp_get_thread_num();

            // will increment num and print statement if openmp was used on compile
            #ifdef _OPENMP
            num += 1;
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
