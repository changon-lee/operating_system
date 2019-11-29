main : instructions.o main.o
	gcc -o main instructions.o main.o

instructions.o : instructions.c
	gcc -c -o instructions.o instructions.c

main.o : main.c
	gcc -c -o main.o main.c

clean : 
	rm *o main
