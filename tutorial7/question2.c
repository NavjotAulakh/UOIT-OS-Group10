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
#define F_NAME "processes.txt"
//Define the structure for the proces priority in the queue
typedef struct
{
    char name[256];
    int priority, pid, runtime;
}proc;

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
proc *delete_pid(int pid);
void push(proc process);
void disp_Process(proc *pro);
void printList(node_queue *list);

int main(int argc, char *argv[])
{
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
            //Tokenize the content to process
            char *token = NULL;
            token = strtok(read_ln, ",\n");
            strcpy(process_1.name, token);
            token = strtok(NULL, ", \n");
            process_1.priority = atoi(token);
            token = strtok(NULL, ", \n");
			process_1.pid = atoi(token);
            token = strtok(NULL, ", \n");
            process_1.runtime = atoi(token);
            push(process_1);
        }
        fclose(filep);
	
		node_queue *values = queue;
		values = values -> next;
		delete_name("emacs");
		delete_pid(12235);
		process_1 = values -> process;
		printf("%-10s %4s %4s %8s \n", "Process name", "Priority", "PID", "Runtime");
		printList(values);
		values = values -> next;
		process_1 = values -> process;
		while(values != NULL){
			if (values -> next == NULL)
			{
				printf("\nin NULL node\n");
				return NULL;
			} else {
				printf("POP \n\n");
				pop();
				printf("%-10s %4s %4s %8s \n", "Process name", "Priority", "PID", "Runtime");
				printList(values);
			}
			values = values -> next;
			process_1 = values -> process;
		}
		
		free(read_ln);
		return 0;
		}
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

//delete_name implemention using learn-c.org linked lists
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

//delete_pid implemention using learn-c.org linked lists
proc *delete_pid(int pid){
	node_queue *current = queue -> next;
	node_queue *prev = queue;
	while(current != NULL){
		tempProcess = current -> process;
		//printf("%d",tempProcess.pid);
		if(tempProcess.pid == pid){
			node_queue *deletedNode = current;
			prev -> next = current -> next;
			free(deletedNode);
			return &tempProcess;
		}
		prev = current;
		current = current -> next;
	}
	printf("The process was not found.\n");
	return NULL;
}

//pop implemention using learn-c.org linked lists
proc *pop()
{
    node_queue *nextNode = NULL;
    if (queue -> next == NULL)
    {
        printf("in NULL node");
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
        printf("%-10s %6d %8d %8d \n", (process->name), process -> priority, process -> pid, process -> runtime);
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