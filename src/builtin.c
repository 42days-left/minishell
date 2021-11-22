/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/21 17:09:18 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *find_value(char *key, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
		i++;
	}
	return ("");
}

void	ft_env(t_env *env_lst)
{
	if (env_lst == NULL)
	{
		printf(RED"ERR\n"RESET);
		exit(2);
	}
	print_envp_lst(env_lst);
}


void	ft_cd(char **envp)
{
	char *path;

	path = find_value("HOME", envp);
	chdir(path);
}

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
	int	i;
	char *tmp;
	char *new_path;
	char **path_arr;
	struct stat s;

	tmp = find_value("PATH", envp);
	path_arr = ft_split(tmp, ':');
	i = 0;
	while(path_arr[i])
	{
		tmp = ft_strjoin("/", str);
		new_path = ft_strjoin(path_arr[i], tmp);
		free(tmp);
		printf("new_path %d: %s\n", i, new_path);
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
		i++;
	}
	return (ft_strdup(str));
}

void	exec_child_process(char *str, char **envp)
{
	int	 fd[2];
	char *path;
	char *cmd[2];

	printf("exec_child_process\n");
	path = find_path(str, envp);
	cmd[0] = str;
	cmd[1] = 0;
	execve(path, cmd, envp);

	free(path);
	exit(1);
}

int		exec_fork(char *str, char **envp)
{
	pid_t	pid;
	int		status;

	printf("exec_fork\n");
	pid = fork();
	if (pid == 0)
	{
		exec_child_process(str, envp);
		return(1);
	}
	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
//	free(tmp);
	return (1);
}
