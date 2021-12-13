#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1


void fx(){

	pid_t pid;

	printf("fx====\n");
	pid = fork();
	if (pid == 0)
	{
		printf("child process\n");
	}

	if (pid > 0) //parent process
	{
		wait(0);
		printf("parent process\n");
	}
}



int main(){
	fx();
		exit(0);
}
