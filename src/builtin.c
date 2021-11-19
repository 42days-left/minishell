/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/19 15:52:27 by yubae            ###   ########.fr       */
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

void	ft_env(char **envp)
{
	get_envp(envp);
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

void	exec_child_process(t_tmp *tmp, char **envp)
{
	int	 fd[2];
	char *path;
	char *cmd[2];
	char *str;
	
	printf("exec_child_process\n");
	str = tmp->str;
	path = find_path(str, envp);
	cmd[0] = str;
	cmd[1] = 0;
	execve(path, cmd, envp);

	free(path);
	exit(1);
}

void		test(t_tmp *tmp)
{
	char *ls = "ls";
	char *wc = "wc";
	t_tmp *new;
	tmp = malloc(sizeof(t_tmp *));
	new = malloc(sizeof(t_tmp *));
	tmp->str = ls;
	tmp->next = new;
	new->str = wc;
	new->next = 0;
}

int		exec_fork(char *str, char **envp)
{
	pid_t	pid;
	int		status;
	char	buf[1024];
//	t_tmp	*tmp;
//	char	*ls;
//	char	*wc;

	printf("exec_fork\n");
//	test(tmp);
//	ls = tmp->str;
//	printf("tmp->str: %s\n", ls);
//	tmp = tmp->next;
//	wc = tmp->str;
//	printf("tmp->str: %s\n", wc);
//	pipe(tmp->fd);
//	pid = fork();
//	if (pid == 0)
//	{
//		exec_child_process(str, envp);
//		return(1);
//	}
//	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
//	free(tmp);
	return (1);
}
