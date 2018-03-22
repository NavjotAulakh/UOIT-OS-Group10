#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MEMORY 1024
#define FILENAME "processes_q2.txt"
int available_memory [MEMORY];

typedef struct{
	char name[256];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;
} proc;

typedef struct node{
	proc process;
	struct node *next;
} node_q;

proc tempProcess;
proc * pop(node_q *queue);
void push(proc process, node_q *queue);
void displayProcess(proc *pro);
void printList(node_q *list);
bool allocateMemory(int *memory, int size);
void deallocateMemory(int *memory);

int main(int argc, char *argv[]){

	const char *cmd = "./process";
	node_q * priority = NULL;
	node_q * secondary = NULL;

	priority = malloc(sizeof(node_q));
	secondary = malloc(sizeof(node_q));

	priority -> next = NULL;
	secondary -> next = NULL;

	for(int i = 0; i < MEMORY; i++){
		available_memory[i] = 0;
	}

	FILE *fp = fopen(FILENAME, "r");
	if(fp == NULL){
		fprintf(stderr, "FILE OPEN ERROR \n");
		exit(1);
	}
	else{
		char *line = NULL;
    	size_t len = 0;
    	ssize_t read;

		while ((read = getline(&line, &len, fp)) != -1) {
			tempProcess.pid = 0;

			char *token = NULL;
			token = strtok(line,",\n");
			strcpy(tempProcess.name,token);
			
			token = strtok(NULL,",\n");
			tempProcess.priority = atoi(token);

			token = strtok(NULL,",\n");
			tempProcess.memory = atoi(token);

			token = strtok(NULL,",\n");
			tempProcess.runtime = atoi(token);

			tempProcess.address = 0;

			if(tempProcess.priority == 0){
				push(tempProcess, priority);
			}
			else{
				push(tempProcess, secondary);
			}
		}
		fclose(fp);

		printf("| > PRIORITY \n");

		while(priority -> next != NULL){
			tempProcess = *pop(priority);

			int status;
			pid_t pid;

			//create process
			pid = fork();

			//child process
			if(pid == 0){
				tempProcess.pid = getpid();
				tempProcess.runtime--;
				allocateMemory(available_memory, MEMORY);
				displayProcess(&tempProcess);
				execv(cmd, argv);
				exit(0);
			}
			//fork failed
			else if(pid < 0){
				status = -1;
			}
			//parent process
			else{
				sleep(tempProcess.runtime);
				kill(pid, SIGTSTP);
				kill(pid, SIGINT);
				waitpid(pid, &status, 0);
				deallocateMemory(available_memory);
			}
		}

		printf("| > SECONDARY \n");
		while(secondary -> next != NULL){
			int status;
			pid_t pid;

			bool mem = true;

			do{
				mem = true;
				tempProcess = *pop(secondary);
				if(!tempProcess.suspended)
				{
					mem = allocateMemory(available_memory,MEMORY);
					if (mem == false){
						printf("NOT ENOUGH MEM: %s\n",tempProcess.name);
						push(tempProcess,secondary);
					}
				}
			}while(!mem && !tempProcess.suspended);

			if(tempProcess.suspended == false){
				//create the process
				pid = fork();

				//child process
				if (pid == 0)
				{
					execv(cmd, argv);
					exit(0);
				}
				//fork failed
				else if (pid < 0) {
					status = -1;
				}
				//parent process
				else {
					tempProcess.pid = pid;
					displayProcess(&tempProcess);
					tempProcess.runtime--;
					tempProcess.suspended = true;
					sleep(1);
					kill(pid, SIGTSTP);
					push(tempProcess,secondary);
				}
			}
			else
			{
				displayProcess(&tempProcess);
				kill(tempProcess.pid, SIGCONT);
				sleep(1);
				kill(tempProcess.pid, SIGTSTP);

				if(tempProcess.runtime <= 1){
					kill(tempProcess.pid,SIGINT);
					waitpid(tempProcess.pid, &status, 0);
					deallocateMemory(available_memory);
				}
				else{
					tempProcess.runtime--;
					push(tempProcess,secondary);
				}

			}
		}
	}
	free(priority);
	free(secondary);
	return 0;
}

proc * pop(node_q * queue){
	node_q * nextNode = NULL;
	if(queue -> next == NULL){
		return NULL;
	}

	nextNode = queue -> next -> next;
	node_q * currentNode = queue -> next;
 	tempProcess = currentNode -> process;

 	free(currentNode);
	queue -> next = nextNode;

	return &tempProcess;
}

void push (proc process, node_q  * queue){
	node_q *current = queue;

	while(current -> next != NULL){
		current = current -> next;
	}

	current -> next =  (node_q *) malloc(sizeof(node_q));
	current -> next -> process = process;
	current -> next -> next = NULL;
}

void displayProcess(proc *process)
{
  if (process != NULL)
  {
    printf("\nName: %10s | Priority: %10d | pid: %10d | Runtime: %10d \n", (process -> name),
      process -> priority, process -> pid, process -> runtime);
  }
}

void printList(node_q *list){
	node_q * current = list;
	current = current -> next;
	while(current != NULL)
	{
		tempProcess = current -> process;
		displayProcess(&tempProcess);
		current = current -> next;
	}
}

bool allocateMemory(int *memory, int size){
	printf("Allocating memory for: %s\n",tempProcess.name);
	sleep(1);

	int allocated = 0;
	int start = 0;

	for(int i = 0; i < size; i++){
		if(memory[i] == 1){
			allocated = 0;
			start = i + 1;
		}
		else{
			allocated++;
		}
		if(allocated == tempProcess.memory){
			tempProcess.address = start;

			for(int k = 0; k < tempProcess.memory; k++){
				memory[k + tempProcess.address] = 1;
			}
			return true;
		}
	}
	return false;
}

void deallocateMemory(int *memory){
	printf("Deallocated memory for: %s\n",tempProcess.name);
	for(int i = 0; i < tempProcess.memory;i++){
		memory[i + tempProcess.address] = 0;
	}
}

