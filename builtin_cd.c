#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	builtin_cd(int argc, char **argv, char **env, int fd)
{
	int		cd;
	char	*search_res;

	if (argc == 1)
	{
		printf("change dir HOME\n");
		chdir(getenv("HOME"));
	}
	else
		chdir("..");
}

int main(int argc, char **argv, char **envp)
{
	printf("BUILT_IN 'cd'\n");
	builtin_cd(2, argv, envp, 1);
}
