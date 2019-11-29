#include "Queue.h"

QUEUE* 
create_queue(){ // Create Queue
    QUEUE* queue;
    queue = (QUEUE*)malloc(sizeof(QUEUE)); // Memory allocation for Queue
    if(queue){ //if queue has address
        queue->front = NULL; 
        queue->rear = NULL;
        queue->count = 0; // Queue Iniialization
        return queue;
    }
    else{
        return NULL;
    }
}

bool enqueue(QUEUE* queue, char in){ 
    QUEUE_NODE* new_node;
    new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE)); // Memory Allocation for Queue_node
    new_node->data = in;
    new_node->next = NULL;
    if(queue->count == 0){ // If Queue is NULL
        queue->front = new_node;
        queue->rear = new_node; // Set front & rear node to NULL
    }
    else{
        queue->rear->next = new_node; // rear->next is current node
        queue->rear = new_node; // current node is rear 
    }

   (queue->count)++; // queue count increment
    
    if(!queue){return false;} // Inappropriate Operation  
    return true;
}

char dequeue(QUEUE* queue){
    if(queue->count == 0) return NULL; // When queue is NULL
    QUEUE_NODE* deleted_node;
    deleted_node = queue->front; // Deletion from front node
    char item = queue->front->data; 
    if(queue->count == 1){
        queue->front == NULL;
        queue->rear == NULL;
        // If Queue has 1 elemenet
    }
    else{
        queue->front = queue->front->next;}
        // Remove front node from Queue
    (queue->count)--; // Queue count decrement
    free(deleted_node); // Free memory of the past front node
    return item;

}

void printqueue(QUEUE* queue){ // print the Queue
    if(queue->count == 0) 
        printf("Queue is empty.\n\n"); // When queue is NULL
    else{
        printf("The queue is:\n");
        int temp_count = queue->count;
        QUEUE_NODE* temp_node = queue->front; // Set Temporary node to queue->front
        while(temp_count != 0){ // Until temp_node is NULL
            printf("%c --> ", temp_node->data);
            temp_node = temp_node->next; // Move on to the next node
            temp_count--;
        }

        printf("NULL\n\n");
    }
}

