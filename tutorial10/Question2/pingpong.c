#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc,char* argv[]){

    

    int proc_id; //Process rank
    int n_proc;  //Number of processes
    double start,end;
    const int PING_PONG_LIMIT = 100;

    //allocation 10 mil double values
    


    //initializes the mpi environment
    MPI_Init(&argc, &argv); 

    //returns the rank of the process in the communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    //returns the size of a communicator
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    if(n_proc !=2){
        fprintf(stderr, "world size must be two for %s \n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    int n_ping_pong = 0;
    int partner_rank = (proc_id +1) % 2;
    double *data = (double*)malloc(10000000*sizeof(double)); //allocation of array

    start = MPI_Wtime(); //start time 
    //ping pong 
    while(n_ping_pong < PING_PONG_LIMIT){
        if(proc_id == n_ping_pong % 2){

            ping_pong_count++;
            MPI_Send(&data,1,MPI_DOUBLE,partner_rank,0,MPI_COMM_WORLD);
        } else {
            MPI_Recv(&data,1,MPI_DOUBLE,partner_rank,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    end = MPI_Wtime(); //end time
    MPI_Finalize();

    printf("Runtime = %f\n", end-start); //runtime
}

