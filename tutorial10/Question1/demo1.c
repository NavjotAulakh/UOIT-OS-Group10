/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

int main (int argc, char* argv[])
{
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initializes the MPI environment
    /*all of MPI's global and internal variables are constructed, 
    **a communicator is formed around all the processes that were spawned
    **unique ranks are assigned to each process
    */
    MPI_Init(&argc, &argv);
    
    // Get the current process id
    /*returns the rank of a process in a communicator
    **each process inside a communicator is assigned an incremental rank starting from zero
    **ranks of the process are primarily used for identification purposes when sending and receiving messages
    */
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    // Get the current number of processes
    /* Returns the size of a communicator
    */
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Display a "Hello world" message from each child/parent
    if (proc_id == MASTER)
    {
        printf( "Hello world from MATER, process %d of %d\n", proc_id, n_proc);
    }
    else
    {
        printf( "Hello world from SLAVE, process %d of %d\n", proc_id, n_proc);
    }

    // Required to terminate all MPI processes
    //cleans up the MPI environment 
    MPI_Finalize();
}
