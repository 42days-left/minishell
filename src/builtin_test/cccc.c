#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include "../include/minishell.h"
#define PATH_MAX 1000

//int builtin_pwd(int argc, char **argv)
//{
//	char strBuffer[PATH_MAX];
//
//	getcwd(strBuffer, PATH_MAX);
//	printf("%s\n", strBuffer);
//	return (0);
//}

extern char **environ;

char			*find_value(char *key, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], key, ft_strlen(key)))
			return (envs[i] + ft_strlen(key) + 1);
	}
	return ("");
}

char			*find_path(char *cmdline, char **envs)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = find_value("PATH", envs);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		printf("paths[%d]: %s ---", i, paths[i]);
		temp = ft_strjoin("/", cmdline);
		new_path = ft_strjoin(paths[i], temp);
		printf("%s\n", new_path);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			printf("new_path 최종: %s\n", new_path);
			return (new_path);
		}free(new_path);
	}
	return (ft_strdup(cmdline));
}

int main(int argc, char *argv[], char **envp)
{
	char **new_argv;
	char command[] = "ls";
	int idx;

	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	
	/* 명령어를 ls로 변경 */
	new_argv[0] = "ls";
	
	/* command line으로 넘어온 parameter를 그대로 사용 */
	for(idx = 1; idx < argc; idx++)
		new_argv[idx] = argv[idx];
	
	/* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미함 */
	new_argv[argc] = NULL;
	char *path = find_path("ls", envp);
	if(execve(path, new_argv, environ) == -1)
	{
		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
		return 1;
	}

	/* ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않습니다. */
	printf("이곳이 이제 ls 명령어라 이 라인은 출력이 되지 않습니다.\n");
	return 0;
}
