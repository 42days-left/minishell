/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/15 16:58:17 by yubae            ###   ########.fr       */
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

char *find_path(char  *str, char **envp)
{
	char *pwd;

	//printf("findpath");
	pwd = getcwd(0, 1024);
	//printf("%s\n", pwd);
	return (pwd);
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
	printf("%s\n", str);
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

	pid = fork();
	if (pid == 0)
	{
		printf("child\n");
		exec_child_process(str, envp);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	close(fd[0]);
	return (1);
}
