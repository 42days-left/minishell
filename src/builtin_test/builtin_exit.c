#include <stdio.h>
#include <stdlib.h>
int builtin_exit(int argc, char **argv, char **env, int fd)
{
	printf("exit\n");
	exit(0);
}

int main(int argc, char **argv, char **envp)
{
	builtin_exit(argc, argv, envp, 0);
}
