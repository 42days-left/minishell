/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/22 16:13:08 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//char *find_value(char *key, t_env *env)
//{
//	int i;
//
//	i = 0;
//	while (envp[i])
//	{
//		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
//			return (envp[i] + ft_strlen(key) + 1);
//		i++;
//	}
//	return ("");
//}

void	ft_export(t_cmd *cmd, t_env *env)
{
	char	*arg1;

	if (((t_token *)cmd->args->next) == NULL)
		print_envp_lst(env);
}

void	ft_env(t_env *env)
{
	if (env == NULL)
		exit_err(2, "env err");
	print_envp_lst(env);
}


void	ft_cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*arg1;

	arg1 = ((t_token *)cmd->args->next->data)->arg;
	if (ft_strncmp(arg1, ".", 1) == 0)
		printf("----cd .\n");
	path = find_value_from_env("$HOME", env);
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


char *find_path(char *str, t_env *env)
{
	int	i;
	char *tmp;
	char *new_path;
	char **path_arr;
	struct stat s;

	tmp = find_value_from_env("$PATH", env);
	path_arr = ft_split(tmp, ':');
	i = 0;
	while(path_arr[i])
	{
		tmp = ft_strjoin("/", str);
		new_path = ft_strjoin(path_arr[i], tmp);
		free(tmp);
		//printf("new_path %d: %s\n", i, new_path);
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
		i++;
	}
	return (ft_strdup(str));
}

void	exec_child_process(char *str, t_env *env)
{
	int	 fd[2];
	char *path;
	char *cmd[2];
	char **envp;

	printf("exec_child_process\n");
	path = find_path(str, env);
	cmd[0] = str;
	cmd[1] = 0;

	envp = malloc(sizeof(char *) * 30);
	env_to_envp(env, envp);
	execve(path, cmd, envp);

	//free(path);
	//free_envp(envp);
	//free(envp);
	exit(1);
}

int		exec_fork(char *str, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*tmp;
	printf("exec_fork\n");
	pid = fork();
	if (pid == 0)
	{
		exec_child_process(str, env);
		return(1);
	}
	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
//	free(tmp);
	return (1);
}
