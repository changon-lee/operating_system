#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

typedef struct Matrix{
	int matrix1[3][3]; /* A matrix */
	int matrix2[3][3]; /* B matrix */
	int multiply[3][3]; /* result */
}Matrix;

void* matrix1(void* arg){
	Matrix* arg_s = (Matrix*)arg;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			arg_s->multiply[i][j] = arg_s->matrix1[i][0] * arg_s->matrix2[0][j];} /* matrix execution 1*/
	}
				

}
void* matrix2(void* arg){
	Matrix* arg_s = (Matrix*)arg;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			arg_s->multiply[i][j] = arg_s->matrix1[i][1] * arg_s->matrix2[1][j];} /*matrix execution 2*/
	}

}

void* matrix3(void* arg){
	Matrix* arg_s = (Matrix*)arg;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			arg_s->multiply[i][j] = arg_s->matrix1[i][2] * arg_s->matrix2[2][j];} /*matrix execution 3*/
	}

}
void print_matrix(Matrix* arg){
	Matrix* arg_p = (Matrix*)arg;
	for(int i=0; i<3; i++){
		for(int j=0;j<3;j++){
			printf("[%2d] ", arg_p->multiply[i][j]);}
		printf("\n\n");
	}
}	



int main(void){
	clock_t start, end;
	float res;
	void* funcs[3];
	
	funcs[0] = matrix1;
	funcs[1] = matrix2;
	funcs[2] = matrix3;
	Matrix* mat_1 = (Matrix*)malloc(sizeof(Matrix));
	srand(time(NULL));
	for(int i=0; i<3;i++){
		for(int j=0; j<3; j++){
			mat_1->matrix1[i][j] = (rand() % 100);
			mat_1->matrix2[i][j] = (rand() % 100);}	/*Matrix Value Setting */
	}
	
	pthread_t three_matrix[3]; /* Three threads */
	start = clock();
	for(int i=0; i<3; i++){
	if(pthread_create(&three_matrix[i],NULL, funcs[i],(void*)mat_1)){
		printf("Pthread Creation Failure.\n");
		exit(10);
	}
	if(pthread_join(three_matrix[i],NULL)){
		printf("Pthread Join Failure.\n");
		exit(10);
	}
	}
	end = clock();
	res = (float)(end - start); /*Execution time*/

	print_matrix(mat_1);
	printf("Three thread access time : %.6f ms\n", res/1000);
	return 0;

}
	
	
		
