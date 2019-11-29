#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#define N 3 /* Matrix Size */

typedef struct Matrix{
	int matrix1[N][N]; /* A matrix */
	int matrix2[N][N]; /* B matrix */
	int multiply[N][N]; /* result */
}Matrix;

void* matrix_integrated(void* arg){
	Matrix* arg_s = (Matrix*)arg;
	for(int i=0; i<N;i++){
		for(int j=0; j<N; j++){
			for(int k=0;k<N;k++){
				arg_s->multiply[i][j] = arg_s->matrix1[i][k] * arg_s->matrix2[k][j];} /* matrix multiply */
		}
	}
				

}
void print_matrix(Matrix* arg){
	Matrix* arg_p = (Matrix*)arg;
	for(int i=0; i<N; i++){
		for(int j=0;j<N;j++){
			printf("[%2d] ", arg_p->multiply[i][j]);} /*Print Matrix */
		printf("\n\n");
	}
}	



int main(void){
	clock_t start, end;   /* Process execution time */
	float res; /* Proesses Execution time result */
	Matrix* mat_1 = (Matrix*)malloc(sizeof(Matrix));
	srand(time(NULL)); /* Prevent identical rand() Value */
	for(int i=0; i<N;i++){
		for(int j=0; j<N; j++){
			mat_1->matrix1[i][j] = (rand() % 100);
			mat_1->matrix2[i][j] = (rand() % 100);} /* matrix value setting */
	}
	
	pthread_t one_matrix;
	start = clock();
	if(pthread_create(&one_matrix,NULL, matrix_integrated,(void*)mat_1)){
		printf("Pthread Creation Failure.\n");
		exit(10);
	}
	if(pthread_join(one_matrix,NULL)){
		printf("Pthread Join Failure.\n");
		exit(10);
	}
	end = clock();
	res = (float)(end - start); /* execution time */

	print_matrix(mat_1); /*print matrix */
	printf("One thread access time : %.6f ms\n", res/1000);
	return 0;

}
	
	
		
