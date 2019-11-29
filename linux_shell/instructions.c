#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "instructions.h"


int pid, status;
int pwd(){
	
	char* argv[] = {"pwd", 0};
	pid = fork();

	switch(pid){
		case -1:// Fork failure case
			printf("fork Error!\n");
			exit(1);
		case 0: // Child Process
			execvp("pwd", argv);
			printf("exec error\n");
			exit(1);

		default: // Wait until child process terminate
			wait(&status);}
	return 0;
	

}


int ls_fundamental(char* str[]){ // Function for ls -l, -al ,-R
	char* argv[4];
	for(int i=0; i< 4; i++){
	argv[i] = str[i]; // Copy string into argv[] string array
	}
	switch(pid){
		case -1:
			printf("fork Error!\n");
			exit(1);
		case 0:
			execv("/bin/ls", argv);
			printf("exec error\n");
			exit(1);

		default:
			wait(&status);}
	return 0;
}

int ls(){
	char* argv[] = {"ls", 0};
	pid = fork();
	
	ls_fundamental(argv); 
	return 0;

}	

int ls_l(){
	char* argv[] = {"ls","-l", 0};
	pid = fork();
	
	ls_fundamental(argv);

}

int ls_R(){
	char* argv[] = {"ls","-R", 0};
	pid = fork();
	
	ls_fundamental(argv); 
	return 0;

}	
int ls_al(){
	char* argv[] = {"ls","-al", 0};
	pid = fork();
	
	ls_fundamental(argv); 
	return 0;

}

int mkdir(char* str){
	char* argv[] = {"mkdir", str, 0}; // str : directory name
	pid = fork();
	switch(pid){
		case -1:
			printf("fork error!\n");
			exit(1);
		case 0:
			execvp("mkdir", argv);
			printf("exec error \n");
			exit(1);

		default:
			wait(&status);
		}
	return 0;
}
int rm(char* str){
	char* argv[] = {"rm","-r", str, 0}; // str : file or directory name.
	pid = fork();
	switch(pid){
		case -1:
			printf("fork error!\n");
			exit(1);
		case 0:
			execvp("rm", argv);
			printf("exec error \n");
			exit(1);

		default:
			wait(&status);
		}
	return 0;
}

