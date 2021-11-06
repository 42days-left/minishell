#include <stdio.h>
#include <unistd.h>

#define PATH_MAX 1000

int builtin_pwd(int argc, char **argv)
{
	char strBuffer[PATH_MAX];

	getcwd(strBuffer, PATH_MAX);
	printf("%s\n", strBuffer);
	return (0);
}

int main(int argc, char **argv)
{
	builtin_pwd(argc, argv);
}
