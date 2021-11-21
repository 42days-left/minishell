/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/21 21:08:08 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//char *find_value(char *key, t_env *env)
//{
//	int i;
//
//	i = 0;
//	while (env[i])
//	{
//		if (!ft_strncmp(env[i], key, ft_strlen(key)))
//			return (env[i] + ft_strlen(key) + 1);
//		i++;
//	}
//	return ("");
//}

//void	ft_env(t_env *env)
//{
//	get_env(env);
//}


void	ft_cd(t_lst *cmds, t_env *env)
{
	char *file;
	t_lst *curr;
	t_lst *tmp;
	char *path;


	curr = ((t_cmd *)(curr->data))->args;
	tmp = curr->next;
	file =  ((t_token *)(tmp->data))->arg;
	printf("ft_cd \n");
	//if (tmp == 0 || file == ".") 
		path = find_value_from_env("$HOME", env);
	printf("%s\n", path);
	chdir(path);
}

void	ft_exit()
{
		printf("exit\n");
		exit(1);
}

void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(0, 1024); // maxsize
	printf("%s\n",pwd);
	free(pwd);
}


char *find_path(char *str, t_env *env)
{
	int	i;
	char *tmp;
	char *new_path;
	char **path_arr;
	struct stat s;

	tmp = find_value_from_env("$PATH", env);
	printf("%s\n", tmp);
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

//void	exec_child_process(char *str, t_env *env)
//{
//	int	 fd[2];
//	char *path;
//	char *cmd[2];
//	
//	printf("exec_child_process\n");
//	path = find_path(str, env);
//	cmd[0] = str;
//	cmd[1] = 0;
//	execve(path, cmd, env);
//
//	free(path);
//	exit(1);
//}

int		exec_fork(char *str, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*tmp;
	printf("exec_fork\n");
	pid = fork();
	if (pid == 0)
	{
	//	exec_child_process(str, env);
		return(1);
	}
	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
//	free(tmp);
	return (1);
}
