#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1


void child_process(char **envp)
{	
	char *cmd[2];
	cmd[0] = "ls";
	cmd[1] = 0;

	execve("/bin/ls", cmd, envp); 
}


int main(int argc, char **argv, char **envp){
	int fd[2];
	pid_t pid;
	char buf[MAX_BUF];
	printf("main2========\n");
//
//	if (pipe(fd) < 0)
//	{
//		printf("pipe error\n");
//		exit(1);
//	}
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
		exit(1);
	}
	printf("asdf\n");
	if (pid > 0) //parent process
	{
//		printf("fd[0]: %d\n", fd[0]);
//		printf("fd[1]: %d\n", fd[1]);
//		close(fd[READ]);
		printf("parent process pid: %d\n", pid);
//		strcpy(buf, "message from parent\n");
//		write(fd[WRITE], buf, strlen(buf));
	}
	else //child process
	{
		child_process(envp);
//		printf("fd[0]: %d\n", fd[0]);
//
//		printf("fd[1]: %d\n", fd[1]);
//		close(fd[WRITE]);
//		printf("pid: %d\n", pid);
//		read(fd[READ], buf, MAX_BUF);
//		printf("child got message : %s\n", buf);
	}
	exit(0);
}
