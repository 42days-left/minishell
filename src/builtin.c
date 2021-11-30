/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/26 19:59:11 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_env *env)
{
	if (env == NULL)
		exit_err(2, "env err");
	print_envp_lst(env);
}

// void	ft_echo(t_lst *cmds)
// {
// 	return ;
// }

void	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;
/*	t_lst	*curr;
	char	*dir;

//	printf("segfault-------\n");
//	if ((t_token *)((t_cmd *)cmds->data)->args->next == 0)
//		path = find_env_from_env("$HOME", env);
//	printf("segfault-------\n");
	curr = ((t_cmd *)cmds->data)->args->next;
//	if (curr == 0)
//		return(chdir(path = find_env_from_env("$HOME", env)));
	//dir = ((t_token *)((t_cmd *)cmds->data)->args->next->data)->arg;
	dir = ((t_token *)curr->data)->arg;
	if (dir[0] == '.' || dir[0] == '~' || dir == 0)
		path = find_env_from_env("$HOME", env);
	else
		path = dir;
	 */
	// char	*arg1;
	// t_token *token;

	// arg1 = ((t_token *)cmd->tokens->next->data)->word;
	// if (ft_strncmp(arg1, ".", 1) == 0)
	// 	printf("----cd .\n");
	// path = find_env_from_env("$HOME", env);
	// if (((t_lst *)cmd->args->next->data)->next == 0)
	// 	path = find_env_from_env("$HOME", env);
	// else
	// {
	// 	arg1 = ((t_token *)cmd->args->next->data)->arg;
	// 	if (arg1 == 0)
	// 	{
	// 		if (arg1[0] != '~')
	// 			path = arg1;
	// 	}
	// }
	// chdir(path);
}

void	ft_exit(int argc, char **argv)
{
		(void)argc;
		(void)argv;
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
	int		i;
	t_env	*tmp;
	char	*new_path;
	char	**path_arr;
	struct stat s;

	tmp = find_env_from_env("$PATH", env);
	path_arr = ft_split(tmp->value, ':');
	i = 0;
	while(path_arr[i])
	{
		tmp->value = ft_strjoin("/", str);
		new_path = ft_strjoin(path_arr[i], tmp->value);
		free(tmp->value);
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

int builtin_function(t_cmd_arg *ca)
{
	int	len;

	len = ft_strlen(ca->argv[0]);
	if (!ft_strncmp(ca->argv[0], "pwd", 3) && len == 3)
		ft_pwd();
	else if (!ft_strncmp(ca->argv[0], "exit", 4) && len == 4)
		ft_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "echo", 4) && len == 4)
		builtin_echo(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "env", 3) && len == 3)
		ft_env(ca->env);
	else if (!ft_strncmp(ca->argv[0], "export", 6) && len == 6)
		ft_export(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "unset", 5) && len == 5)
		builtin_unset(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "cd", 2) && len == 2)
		ft_cd(ca->argc, ca->argv, ca->env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute1(t_cmd_lst *cmds, t_env *env)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env);
	builtin_function(cmd_arg);
	return (EXIT_SUCCESS);
}


int	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	curr = cmds;
	// count = lst_size(curr);
	count = 1;
	if (count == 1)
		execute1(cmds, env);
	// else
	// 	execute2(cmds, env);
	return (1);
}
