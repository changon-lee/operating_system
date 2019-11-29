#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>

volatile int balance = 1000000; 
void* withdraw(void* arg);

pthread_mutex_t lck;
int main(){
	int a=0;
	int b=0;
	int original_a = 0; /* If Pthread creation fail, To save original a value */
	
	printf("Current Deposit : %d\n", balance);
	printf("How many threads to create? : ");
	scanf("%d",&a);
	original_a = a;
	printf("How much money to withdraw? : ");
	scanf("%d",&b);  /* User input */
	pthread_t t[a];
	pthread_mutex_init(&lck, NULL);  /* Mutex initiate */

	for(int i=0; i<original_a; i++){

	if(pthread_create(t+i, NULL, withdraw, (void*) b)){
		printf("Waiting...\n");  /* Pthread creation failed, Wait for other threads to complete */
		sleep(1); /* Wait */
		if(pthread_create(t+i, NULL, withdraw, (void*) b)){ 
			printf("Pthread Creation Error\n");   /* Pthread creation failed again */
			a-=1;}

}}
	for(int i=0; i<original_a;i++){
	if(pthread_join(t[i],NULL)){
		printf("Pthread Join Failure.\n"); /*Pthread Join failed */
}
}
			
	
	printf("All done : Balance is $%d\n", balance);
	printf("%d Threads created, %d Threads failed to create\n", a, (original_a)-a);
	printf("Original Predicted Value is $%d\n", 1000000-(a*b));
	return 0;


}

void* withdraw(void* arg){
	int amount = (int)arg;
	if(balance >= amount){
 		pthread_mutex_lock(&lck);  /* Mutex Lock */
		balance -= amount;
		pthread_mutex_unlock(&lck); /* Mutex Unlock */
		printf("ATM gives user %d\n",amount);
}
}
