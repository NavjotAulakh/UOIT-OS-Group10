#include<stdio.h>
#include<mpi.h>

#define MASTERTAG 1
#define SLAVETAG 4

int processNumber, numOfProcesses, lowerBound, upperBound, allocatedPortion, i, j, k;
double matrixA[100][100], matrixB[100][100], matrixC[100][100];
MPI_Status status;
MPI_Request request;

void initializeAB()
{
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            matrixA[i][j] = j;
        }
    }
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            matrixB[i][j] = j;
        }
    }
}

void printArray()
{
    for (i = 0; i < 100; i++) {
        printf("\n");
        for (j = 0; j < 100; j++)
            printf("%8.2f  ", matrixA[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < 100; i++) {
        printf("\n");
        for (j = 0; j < 100; j++)
            printf("%8.2f  ", matrixB[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < 100; i++) {
        printf("\n");
        for (j = 0; j < 100; j++)
            printf("%8.2f  ", matrixC[i][j]);
    }
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcesses);
	
    //master process
    if (processNumber == 0) {
        initializeAB();
        for (i = 1; i < numOfProcesses; i++) {
            allocatedPortion = (100 / (numOfProcesses - 1));
            lowerBound = (i - 1) * allocatedPortion;
            if (((i + 1) == numOfProcesses) && ((100 % (numOfProcesses - 1)) != 0)) {
                upperBound = 100;
            } else {
                upperBound = lowerBound + allocatedPortion;
            }
            MPI_Isend(&lowerBound, 1, MPI_INT, i, MASTERTAG, MPI_COMM_WORLD, &request);
            MPI_Isend(&upperBound, 1, MPI_INT, i, MASTERTAG + 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&matrixA[lowerBound][0], (upperBound - lowerBound) * 100, MPI_DOUBLE, i, MASTERTAG + 2, MPI_COMM_WORLD, &request);
        }
    }
    //broadcast matrixB to all the slaves
    MPI_Bcast(&matrixB, 100*100, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
    //slave processes
    if (processNumber > 0) {
        MPI_Recv(&lowerBound, 1, MPI_INT, 0, MASTERTAG, MPI_COMM_WORLD, &status);
        MPI_Recv(&upperBound, 1, MPI_INT, 0, MASTERTAG + 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrixA[lowerBound][0], (upperBound - lowerBound) * 100, MPI_DOUBLE, 0, MASTERTAG + 2, MPI_COMM_WORLD, &status);
        for (i = lowerBound; i < upperBound; i++) {
            for (j = 0; j < 100; j++) {
                for (k = 0; k < 100; k++) {
                    matrixC[i][j] += (matrixA[i][k] * matrixB[k][j]);
                }
            }
        }
        MPI_Isend(&lowerBound, 1, MPI_INT, 0, SLAVETAG, MPI_COMM_WORLD, &request);
        MPI_Isend(&upperBound, 1, MPI_INT, 0, SLAVETAG + 1, MPI_COMM_WORLD, &request);
        MPI_Isend(&matrixC[lowerBound][0], (upperBound - lowerBound) * 100, MPI_DOUBLE, 0, SLAVETAG + 2, MPI_COMM_WORLD, &request);
    }
	
    //master process
    if (processNumber == 0) {
        for (i = 1; i < numOfProcesses; i++) {// untill all slaves have handed back the processed data
            MPI_Recv(&lowerBound, 1, MPI_INT, i, SLAVETAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&upperBound, 1, MPI_INT, i, SLAVETAG + 1, MPI_COMM_WORLD, &status);
            MPI_Recv(&matrixC[lowerBound][0], (upperBound - lowerBound) * 100, MPI_DOUBLE, i, SLAVETAG + 2, MPI_COMM_WORLD, &status);
        }
        printArray();
    }
	
    MPI_Finalize();
    return 0;
}
