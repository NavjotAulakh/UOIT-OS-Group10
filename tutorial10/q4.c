#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0


int isPrime(int x){
    if (x <= 1) {
        return 0;
    }
    else if (x <= 3){
        return 1;
    }
    else {
        for (int i = sqrt(x); i > 1; i--)
        {
            if (x % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
}

void master(int n_proc)
{
    int lowerBound, upperBound, segment, numOfPrimes, count, recv;
    int searchSpace[n_proc][2];
    lowerBound = 1; upperBound = 2;
    // Get user to input lower and upper bound.
    printf("Please enter the lower bound of the search space.\n");
    int err = scanf("%d", &lowerBound);
    if (err == EOF){
        printf("Error accepting user input. Crashing.");
        exit(4);
    }
    printf("Please enter the upper bound of the search space.\n");
    err = scanf("%d", &upperBound);
    if (err == EOF){
        printf("Error accepting user input. Crashing.");
        exit(4);
    }

    // Setup variables.
    segment = (upperBound - lowerBound) / (n_proc -1 ); 
    numOfPrimes = lowerBound + segment / log(lowerBound+segment);
    count = 0;

    int result[numOfPrimes+50];
    int primes[n_proc][numOfPrimes+50];
    for (int i = 0; i < n_proc; i++)
    {
        for (int j = 0; j < numOfPrimes+50; j++)
        {
            primes[i][j] = upperBound+500;
        }
    }

    // Send bounds to slaves, and setup search space.
    for (int i = 1; i < n_proc; i++)
    {
        searchSpace[i][0] = lowerBound;
        searchSpace[i][1] = lowerBound + segment;
        MPI_Send(searchSpace[i], 2, MPI_INT, i, 2, MPI_COMM_WORLD);
        lowerBound = lowerBound + segment + 1;
    }

    MPI_Status status;

    // Recieve and store prime numbers.
    for (int i = 1; i < n_proc; i++)
    {
        printf("\nSearch Space: [%d, %d]. \nPrimes: [", searchSpace[i][0], searchSpace[i][1]);
        MPI_Recv(result, numOfPrimes+50, MPI_INT, i, MPI_ANY_TAG,
            MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_INT, &recv);
        for (int k = 0; k < recv; k++)
        {
            primes[i][k] = result[k];
            if ((primes[i][k] >= searchSpace[i][0]) & (primes[i][k] <= searchSpace[i][1]))
            {
                printf("%d ", primes[i][k]);
                count++;
            }
        }
        printf("]\n\n");
    }
    

    // Print the desired output.
    
    printf ("Found %d primes.\n", count);
}

void slave()
{
    int bounds[2] = { 0 }; // Bounds to search in
   
    MPI_Recv(bounds, 2, MPI_INT, MASTER, MPI_ANY_TAG,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int numOfPrimes = bounds[1] / log(bounds[1]);
    int oddNum = bounds[0];
    int primes[numOfPrimes+10];
    int count = 0;

    while(count < numOfPrimes+10){
        primes[count] = bounds[1] + 100;
        count++;
    }
    count = 0;

    if(oddNum % 2 == 0){
        oddNum -= 1;
    }

    if ((oddNum  < 3) & (bounds[0] >= 0))
    {
        primes[count] =  2;
        count++;
    }

    while (oddNum <= bounds[1]){
        if (isPrime(oddNum)){
            primes[count] = oddNum;
            count++;
        }
        oddNum += 2;
    }

    MPI_Send(primes, count, MPI_INT, 0, 1, MPI_COMM_WORLD);
    
}


int main(){
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initialize MPI
    MPI_Init(0, NULL);
    
    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    if (proc_id == MASTER)
    {
        // Execute the master process.
        master(n_proc);
    }
    else
    {
        // Execute the slave process.
        slave(proc_id);
    }

    // Required to terminate all MPI processes
    MPI_Finalize();
    return 0;
}
