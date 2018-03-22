#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// define variables and types
struct proc 
{
    char parent[256];   // name of the parent process
    char name[256];     // name of the process
    int *priority;      // process priority
    int *memory;        // memory used by the process (in MB)
};

// binary tree
struct proc *proc_tree (char name)
{
    // allocate memory for a new node
    struct proc *node = (struct proc*)malloc(sizeof(struct proc));

    // assign data to this node
    *node->name = name;

    return(node);
};

// print tree 
void print_preorder(struct proc *proc_tree)
{
    // return if tree is empty
    if (proc_tree == NULL)
        return;

    // print data of node
    printf("%s", proc_tree->name);

    // iterate recursively on the left subtree
    print_preorder(proc_tree->name);

    // iterate recursively on the right subtree
    print_preorder(proc_tree->name);
}

int main(void) 
{
    // create root of binary tree
    struct proc *root = proc_tree;

    // open the file for reading the contents of the process tree
    FILE *fp = fopen("process_tree.txt", "r");

    //read contents of the process tree
    fscanf(fp, "%s", root);

    return 0;
}