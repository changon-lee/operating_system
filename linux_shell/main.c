#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instructions.h"
#include <stdio_ext.h> // __fpurge(stdin)
#define size 30

int main(){
	char str[size]; // Input String
	printf("----------------My First Shell-----------------\n");
	printf("     pwd, ls(-l, -R, -al), mkdir, rm, exit\n");
	

	while(true)
	{
		printf("-> ");
		scanf("%[^\n]s", str); // Get string including " " char type
		__fpurge(stdin);
	char *saved_value[size] = {NULL, }; // Cut string and save it to saved_value
	char saved_str[size]; // Save origial string before strtok
	int i=0;

	for(int j=0;j<size; j++){
		saved_str[j] = str[j]; // Saving
	}

	// For mkdir
	char *ptr = strtok(saved_str, " "); 
	while(ptr !=NULL)
	{
		saved_value[i] = ptr;
		i++;
		ptr = strtok(NULL," ");
		
	} // Cut the string and save the value to saved_value[i]

	// Compare String
	if(!strcmp("pwd",str))
		pwd(); 
	if(!strcmp("ls",str))
		ls();
	if(!strcmp("ls -l", str))
		ls_l();
	if(!strcmp("ls -R", str))
		ls_R();
	if(!strcmp("ls -al", str))
		ls_al();
	if(!strcmp("exit",str))
		break;
	if(!strcmp("mkdir", saved_value[0])){
	for(int j=i-1;j>0;j--){ // Can get several inputs 
		mkdir(saved_value[j]);
		printf("%s is created to current directory.\n", saved_value[j]);}}
	if(!strcmp("rm", saved_value[0])){
	for(int j=i-1;j>0;j--){ // Can get several inputs
		rm(saved_value[j]);
		printf("%s is removed from current directory.\n", saved_value[j]);}
	}
}
	

	return 0;

}

