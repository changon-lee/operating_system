main : Queue.o Stack.o Stack_Queue_Main.o
	gcc -o main Queue.o Stack.o Stack_Queue_Main.o

Queue.o : Queue.c
	gcc -c -o Queue.o Queue.c

Stack.o : Stack.c
	gcc -c -o Stack.o Stack.c

Stack_Queue_Main.o : Stack_Queue_Main.c
	gcc -c -o Stack_Queue_Main.o Stack_Queue_Main.c

clean :
	rm *.o main
