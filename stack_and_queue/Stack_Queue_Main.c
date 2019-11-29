#include <stdio.h>
#include <string.h> // malloc, strtok
#include <stdio_ext.h> // __fpurge(stdin)
#include "Stack.h"
#include "Queue.h"

#define BUFFER_SIZE 30
int main(){
    STACK* stack_ptr;
    stack_ptr = create_stack(); // create stack_ptr
    QUEUE* queue_ptr;
    queue_ptr = create_queue(); // create queue_ptr
 
    int choice; // Selection
    instructions();
    printf("? ");
    scanf("%d", &choice);
    __fpurge(stdin);     // Clean Buffer
    while(choice != 5){ 
        char s1[BUFFER_SIZE+20]; // Maximum 
		char *saved_value[BUFFER_SIZE]={NULL, } ; // Array pointer declaration, NULL initialization
        int i=0; 
        switch (choice) {
            case 1: // Stack, Push selected
                printf("Enter an integer : ");
                scanf("%[^\n]s", s1); // Input restriction until 49 
                
                __fpurge(stdin); 
                                           
                char *ptr =  strtok(s1," "); // Cut string by " " 
                
                while(ptr != NULL) // Loop until ptr is NULL
                {
                    saved_value[i] = ptr; // Memory address to Pointer Array
                    i++; // Index ++
                    ptr = strtok(NULL, " "); // Cut next string and return it 
                }                
       
                for(int i=0; i<BUFFER_SIZE;i++)
                {
                    if(saved_value[i]!=NULL) // If element is not NULL
                        push(stack_ptr, *saved_value[i]); // Push array pointer value to stack

                }
                printstack(stack_ptr); // Print stack
                
                break;

            case 2: // Stack, Pop Selected
               
                if(stack_ptr->count != 0){ // When Stack is not NULL
                    
                    char temp_pop = pop(stack_ptr); // Store popped value in temp_pop
                    printf("The popped value is %c.\n", temp_pop); // print result 
                }
                printstack(stack_ptr); // Print stack
                break;
            case 3: // Queue, Enqueue Selected
                printf("Enter an integer : "); 
                scanf("%[^\n]49s", s1);
                __fpurge(stdin);
                char *ptr_queue = strtok(s1," ");

                while(ptr_queue != NULL){
                    saved_value[i] = ptr_queue;
                    i++; 
                    ptr_queue = strtok(NULL," "); 
                }
                //Same with Stack CASE 1

                for(int i=0; i<BUFFER_SIZE; i++){
                    if(saved_value[i]!=NULL) // If element is not NULL
                        enqueue(queue_ptr, *saved_value[i]); // Enqueue array pointer value to queue
                }
                printqueue(queue_ptr); // Print Queue
                break;
             case 4:
                if(queue_ptr->count != 0){ // When Queue is not NULL
                    char item = dequeue(queue_ptr); // Store Dequeued value in item
                    printf("%c has been dequeued.\n", item); // print result
                }
                printqueue(queue_ptr); // print Queue
                break;

            default: // When input is invalid value
                printf("Invalid choice.\n\n");
                instructions(); // Print instructions again 
                break;

        }

        printf("? ");
        scanf("%d", &choice);
        __fpurge(stdin);
    }

    return 0;
}
                           

