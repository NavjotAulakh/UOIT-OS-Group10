#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define F_NAME "processes.txt"
typedef struct{
	char name[256];
    int runtime, pid, priority;
	
}proc;

typedef struct node{
	proc process;
	struct node *next;
}node_queue;

node_queue *queue;

void push (proc new_process);

int main(void) {
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

		printf("%-10s %4s %4s %8s \n", "Process name", "Priority", "PID", "Runtime");
		while(values != NULL){
			proc process_1 = values -> process;
			disp_Process(process_1);
			printf("%-10s %6d %8d %8d \n", process_1.name, process_1.priority, process_1.pid, process_1.runtime);
			values = values -> next;
		}
		free(read_ln);
		return 0;
	}
}

//push implemention using learn-c.org linked lists
void push(proc new_process){
    node_queue *current = queue;

    while(current -> next != NULL){
        current = current -> next;
    }
    current -> next = (node_queue *) malloc(sizeof(node_queue));
    current -> next -> process = new_process;
    current -> next -> next = NULL;
}