all : rc MallocTooMuch HeapandStack
rc : recursivecall.o
	gcc -o $@ $< 
MallocTooMuch : MallocTooMuch.o
	gcc -o $@ $<
HeapandStack : HeapandStack.o
	gcc -o $@ $< 
recursivecall.o : recursivecall.c
	gcc -c -o $@ $<
MallocTooMuch.o : MallocTooMuch.c
	gcc -c -o $@ $<
HeapandStack.o : HeapandStack.c
	gcc -c -o $@ $< 
clean : 
	rm *o rc MallocTooMuch HeapandStack
