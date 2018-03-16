#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
//Define global variables/constants/constaints
#define SHELL "/bin/sh"
#define F_NAME "processes_q5.txt"
//Define the structure for the proces priority in the queue
typedef struct
{
    char name[256];
    int priority, pid, runtime;
} proc;
//Define the structure for the linked list
typedef struct node
{
    proc process;
    struct node *next;
} node_queue;
//Initialize a linked list with a queue with their functions and processes
node_queue *queue;
proc *pop();
proc tempProcess;
proc *delete_name(char *name);
void push(proc process);
void disp_Process(proc *pro);
void printList(node_queue *list);

int main(int argc, char *argv[])
{
    const char *init_sigtrap = "./process";
    queue = NULL;
    queue = malloc(sizeof(node_queue));
    queue->next = NULL;

    //Initialize the file pointer and open the file to read
    FILE *filep = fopen(F_NAME, "r");
    if (filep == NULL)
    {
        fprintf(stderr, "File Could Not Be Opened. \n");
        exit(1);
    }else{
        char *read_ln = NULL;
        size_t len = 0;
        ssize_t read;
        proc process_1;
        while ((read = getline(&read_ln, &len, filep)) != -1)
        {
            //Initialize pid to 0 as its not provided in txt file
            process_1.pid = 0;
            //Tokenize the content to process
            char *token = NULL;
            token = strtok(read_ln, ",\n");
            strcpy(process_1.name, token);
            token = strtok(NULL, ", \n");
            process_1.priority = atoi(token);
            token = strtok(NULL, ", \n");
            process_1.runtime = atoi(token);
            push(process_1);
        }
        fclose(filep);
        //Implementation of linked list with learn-c.org example
        node_queue *current = queue;
        current = current -> next;
        while (current != NULL)
        {
            process_1 = current -> process;
            if (process_1.priority == 0)
            {
                int proc_status;
                const char *command = process_1.name;
                pid_t pid;
                //Parent forks to create process
                pid = fork();
                //Child process executes the arguments with command through sigtrap
                if (pid == 0)
                {
                    execv(command, argv);
                    delete_name(process_1.name);
                    execv(init_sigtrap, argv);
                    exit(0);
                }
                //If fork fails change state to -1
                else if (pid < 0) 
                {
                    proc_status = -1;
                }else{
                    sleep(process_1.runtime);
                    kill(pid, SIGINT);
                    waitpid(pid, &proc_status, 0);
                    if (proc_status == 0)
                    {
                        process_1.pid = pid;
                        disp_Process(&process_1);
                        current = current->next;
                    }
                }
            }else{
                int proc_status;
                const char *command = process_1.name;
                pid_t pid;
                //Parent forks to create process
                pid = fork();
                //Child process executes the intial command
                if (pid == 0)
                {
                    execv(command, argv);
                    exit(0);
                } 
                //If fork fails change state to -1
                else if (pid < 0)
                {
                    proc_status = -1;
                } else {
                    sleep(process_1.runtime);
                    kill(pid, SIGINT);
                    waitpid(pid, &proc_status, 0);
                    if (proc_status == 0)
                    {
                        process_1.pid = pid;
                        disp_Process(&process_1);
                        current = current -> next;
                        pop();
                    }
                }
            }
        }
    }
    return 0;
}

//push implemention using learn-c.org linked lists
void push(proc process)
{
    node_queue *currentProcess = queue;
    while (currentProcess -> next != NULL)
    {
        currentProcess = currentProcess -> next;
    }
    currentProcess -> next = (node_queue *)malloc(sizeof(node_queue));
    currentProcess -> next -> process = process;
    currentProcess -> next -> next = NULL;
}

//Delete_name implemention using learn-c.org linked lists
proc *delete_name(char *name)
{
    node_queue *currentProcess = queue -> next;
    node_queue *previous = queue;
    while (currentProcess != NULL)
    {
        tempProcess = currentProcess -> process;
        if (strcmp(tempProcess.name, name) == 0)
        {
            node_queue *deleteNode = currentProcess;
            previous -> next = currentProcess -> next;
            free(deleteNode);
            return &tempProcess;
        }
        previous = currentProcess;
        currentProcess = currentProcess -> next;
    }
    printf("Process was not found.\n");
    return NULL;
}

//pop implemention using learn-c.org linked lists
proc *pop()
{
    node_queue *nextNode = NULL;
    if (queue -> next == NULL)
    {
        printf("in NULL node\n");
        return NULL;
    }
    nextNode = queue -> next -> next;
    node_queue *currentNode = queue -> next;
    tempProcess = currentNode -> process;
    free(currentNode);
    queue -> next = nextNode;
    return &tempProcess;
}

//Function prints the process structure
void disp_Process(proc *process)
{
    if (process != NULL)
    {
        printf("\nProcess Name: %7s | Priority: %4d | pid: %5d | Runtime: %2d \n",
            (process->name), process -> priority, process -> pid, process -> runtime);
    }
}

//printList implemention using learn-c.org linked lists
void printList(node_queue *list)
{
    node_queue *currentProcess = list;
    currentProcess = currentProcess -> next;
    while (currentProcess != NULL)
    {
        tempProcess = currentProcess -> process;
        disp_Process(&tempProcess);
        currentProcess = currentProcess -> next;
    }
}