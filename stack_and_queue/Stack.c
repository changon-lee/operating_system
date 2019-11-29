#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//Create Stack
STACK*
create_stack(){
    STACK* stack = (STACK*)malloc(sizeof(STACK)); // Stack Memory Allocation
    stack->count = 0; // Stack count initialization
    stack->top = NULL; 
    return stack;
}

bool push(STACK* stack, char in){ //Push Function
    STACK_NODE* new_node = (STACK_NODE*)malloc(sizeof(STACK_NODE)); //Stack node memory allocation
    new_node->data = in; 
    new_node->link = stack->top; // Link node->link to stack->top
    stack->top = new_node; // stack->top is new_node
    (stack->count)++; // stack count increment
    return true;

}

char pop(STACK* stack){ // Pop Function
    if(stack->count == 0) // When stack is NULL
        return NULL;
    else
    {
        STACK_NODE* temp = stack->top; 
        char data_out = stack->top->data; // Data to Pop

        stack->top = stack->top->link; //Re-initialization for stack->top
        free(temp); // Free the top node
        (stack->count)--; // stack count decrement
        return data_out; 
    }
}

void printstack(STACK* stack){ // Print the stack
    if(stack->count == 0)
        printf("The stack is empty.\n\n"); // When stack is NULL
    else{
        printf("The stack is:\n");

        int temp = stack->count;
        STACK_NODE* temp_node = stack->top; // Move node from top to bottom
        while(temp != 0){
            char print_node = (temp_node->data); 
            printf("%c --> " , print_node); // Print data of current node
            
            temp_node = temp_node->link; // Move to the next node
            temp--;
        }
     printf("NULL\n\n"); 
    }
}

void instructions(void){ // Instruction Function
    printf("Enter choice:\n"
            "1 to push a value on the stack\n" // Case 1 
            "2 to pop a value off the stack\n" // Case 2
            "3 to add an item to the queue\n" // Case 3
            "4 to remove an item from the queue\n" // Case 4
            "5 to end\n"
            "* Do not enter items more than 30 letters *");
}


