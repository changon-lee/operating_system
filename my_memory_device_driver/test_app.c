#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 100

int main(void){
	int fd;
	int result;

	char* in = (char*)malloc(sizeof(char)*MAX_SIZE);
	char* out = (char*)malloc(sizeof(char)*MAX_SIZE*100);

	if((fd = open("/dev/mydevicefile", O_RDWR)) < 0){
		perror("open error");
		return -1;
	}
	

	printf("User String Input : ");
	scanf("%s", out);
	
	result = write(fd, out, strlen(out));
	printf("String length : %d\n", strlen(out));
	printf("Result : %d\n", result);

	read(fd, in, MAX_SIZE);
	printf("Output String : %s\n", in);
	
	free(in);
	free(out);

	close(fd);

	return 0;

}
