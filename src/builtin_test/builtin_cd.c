#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int builtin_cd(int argc, char **argv, char **env, int fd)
{
	int		cd;
	char	*search_res;


	if (argc == 1)
		chdir(getenv("HOME"));
	else
		chdir(argv[1]);
	return(0);
}

int main()
{
	int argc = 1;
	char **argv = 0;
	char **envp = 0;

	printf("%s\n", getenv("HOME"));
	builtin_cd(argc, argv, envp, 1);
}
