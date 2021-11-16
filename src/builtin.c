/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/15 20:19:45 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char *str)
{
		printf("exit\n");
		free(str);
		exit(1);
}

void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(0, 1024); // maxsize
	printf("%s\n",pwd);
	free(pwd);
}

char *find_value(char *key, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
	}
	return ("");
}

char *find_path(char  *str, char **envp)
{
	int	i;
	char *tmp;
	char *new_path;
	char **path_arr;
	struct stat s;

	printf("3. findpath");
	tmp = find_value("PATH", envp);
	path_arr = ft_split(new_path, ':');
	i = 0;
	while(path_arr[i])
	{
		tmp = ft_strjoin("/", str);
		new_path = ft_strjoin(path_arr[i], tmp);
		free(tmp);
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
	}
	return (ft_strdup(str));
}

void	exec_child_process(char *str, char **envp)
{
	int	 fd[2];
	char *path;
	
	path = find_path(str, envp);

	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(path, &str, envp);
	printf("4. child_process\n");
	free(path);
	exit(1);
}

int		exec_fork(char *str, char **envp)
{
	pid_t	pid;
	int		res;
	int		status;
	char	*path;
	int		fd[2];
	
	printf("1. exec_fork\n");
	pid = fork();
	if (pid == 0)
	{
		printf("2. child\n");
		exec_child_process(str, envp);
	}
	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
	return (1);
}
