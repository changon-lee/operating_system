bank : main

mat1 : main2

mat2 : main3

main3 : matrix2.o
	gcc -o main3 matrix2.o -pthread
main2 : matrix.o
	gcc -o main2 matrix.o -pthread
main : banking.o
	gcc -o main banking.o -pthread
banking.o : banking.c
	gcc -c -o banking.o banking.c
matrix.o : matrix.c
	gcc -c -o matrix.o matrix.c
matrix2.o : matrix2.c
	gcc -c -o matrix2.o matrix2.c
clean : 
	rm *o main
