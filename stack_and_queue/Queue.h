#ifndef ADT_QUEUE
#define ADT_QUEUE

#include <stdio.h>
#include <stdlib.h> //malloc
#include <stdbool.h> // bool
// Queue NODE
typedef struct node{
    char data;
    struct node* next;
}QUEUE_NODE;

//QUEUE
typedef struct{
    int count;
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
}QUEUE;

//Operations
QUEUE*  create_queue();
bool enqueue    (QUEUE* queue, char in);
char dequeue    (QUEUE* queue);
void printqueue(QUEUE* queue);

#endif
