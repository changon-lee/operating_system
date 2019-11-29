#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ONE_MEG 1048576

long *MemoryPtr;
static double NumberOfAllocations = 0; 
void RecursiveRoutine(int,int  );
char *commas(unsigned long amount);

unsigned long FirstStackLocation;
unsigned long FirstHeapLocation;
int main(int argc, char *argv[]){
	
	char MemoryFunction[32];
	int Function = 0;
	int TopOfStack;
	int Counter = 0;
	int* TopOfHeap = (int*)malloc(sizeof(int*));
	FirstStackLocation = (unsigned long)&(TopOfStack);
	FirstHeapLocation = (unsigned long)(TopOfHeap);
	printf("First location on stack : %s\n", commas((unsigned long)FirstStackLocation));
	printf("First location on Heap : %s\n", commas((unsigned long)FirstHeapLocation));
	
	
	if(argc<2){
		printf("Usage : %s <Read|Write|Nothing>\n", argv[0]);
		exit(1);
	}	
	
	
	strcpy(MemoryFunction, argv[1]);

	
	if(strncmp(MemoryFunction, "Nothing", 7) == 0) Function = 1;
	if(strncmp(MemoryFunction, "Read", 4) == 0) Function = 2;
	if(strncmp(MemoryFunction, "Write",5) == 0) Function = 3;
	if(Function == 0){
		printf("Unable to recognize the Read|Write|Nothing portion of the command\in");

		return;
	}

	/* Call Recursive Routine */
	RecursiveRoutine(0, Function);


	
}


#define STACK_ALLOC ONE_MEG/20
#define HEAP_ALLOC ONE_MEG/10
void RecursiveRoutine(int RecursiveDepth,int FunctionType){
	char StringTop[32]; 	
	char StringBottom[32];
	char HeapTop[32];
	char HeapBottom[32];
	long* TempPointer;
	long TempHeap;
	
		MemoryPtr = (long*)malloc(HEAP_ALLOC);	/*Heap Allocation*/
		char Temp[STACK_ALLOC];			/*Stack Allocation*/
		if(MemoryPtr == 0){	/*if allocation failed */
			printf("The program is ending because we could allocate no more memory.\n");
			printf("Total megabytes allocated on Stack = %.3lf\n", NumberOfAllocations/(double)20);	 
			printf("Total megabytes allocated on Heap = %.3lf\n", NumberOfAllocations/(double)10);

			exit(0);
		}

		NumberOfAllocations++;
				
		TempPointer = MemoryPtr;
		if(FunctionType == 2){	/*Read */
			while((unsigned long)TempPointer < (unsigned long)((long)MemoryPtr + HEAP_ALLOC)){
				TempHeap = TempPointer[0];
				TempPointer = (long*)((unsigned long)TempPointer + 4096);
			}
		}
		if(FunctionType == 3){	/*Write */
			while((unsigned long)TempPointer < (unsigned long)((long)MemoryPtr + HEAP_ALLOC)){
				TempPointer[0] = TempHeap;
				TempPointer = (long*)((unsigned long)TempPointer + 4096);
		}
		}
	strcpy(HeapTop, commas((unsigned long)(FirstHeapLocation)));
	strcpy(HeapBottom, commas((unsigned long)MemoryPtr));
	strcpy(StringTop, commas((unsigned long)(FirstStackLocation)));
	strcpy(StringBottom, commas((unsigned long)&(Temp[STACK_ALLOC])));
	printf("Iteration = %3d: Heap Top/Bottom/Bytes : %s %8s %d\n", RecursiveDepth, HeapTop, HeapBottom, (unsigned long)MemoryPtr - FirstHeapLocation); /*Heap Location */
	printf("Iteration = %3d: Stack Top/Bottom/Bytes: %s %s %d\n",RecursiveDepth, StringTop,StringBottom, FirstStackLocation - (unsigned long)&(Temp[STACK_ALLOC])); /*Stack Location*/
	RecursiveDepth++;
	RecursiveRoutine(RecursiveDepth,FunctionType);
}

#define	BASE 16
#define GROUP 4
#define MAXTEXT 25

int prepend(char *, unsigned, char *);
int preprintf(char *, unsigned, char *, ...);

char *commas(unsigned long amount)
{
	short i;
	short offset = MAXTEXT -1;
	short place;

	static char text[MAXTEXT];
	for(i = 0; i < MAXTEXT ; i++)
		text[i] = '\0';

	for(place = 0;amount >0; ++place)
	{
		if(place % GROUP == 0 && place > 0)
			offset = prepend(text,offset,",");
		offset = preprintf(text,offset,"%X",amount % BASE);
		amount /= BASE;
	}
	return (offset >= 0) ? text + offset : NULL;
}

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

int prepend(char *buf, unsigned offset, char *new_str)
{
	int new_len = strlen(new_str);
	int new_start = offset - new_len;
	if(new_start >= 0)
		memcpy(buf + new_start,new_str, new_len);
	return new_start;
}

int preprintf(char *buf, unsigned offset, char* format, ...)
{
	int pos = offset;
	char *temp = malloc(BUFSIZ);

	if(temp)
	{
		va_list args;
		
		va_start(args,format);
		vsprintf(temp,format,args);
		pos = prepend(buf,offset,temp);
		va_end(args);
		free(temp);
	}
	return pos;
}
