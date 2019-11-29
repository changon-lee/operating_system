#ifndef STACK_ADT
#define STACK_ADT

#include <stdio.h>
#include <stdbool.h> // bool
//Stack Node
typedef struct stack_node{
    char data;
    struct stack_node *link;
}STACK_NODE;

//Stack ADT
typedef struct a{
    int count;
    STACK_NODE *top;
}STACK;

//Interface

STACK* create_stack();
bool push(STACK *stack, char in);
char pop(STACK *stack);
void printstack(STACK* stack);
void instructions(void);

#endif

