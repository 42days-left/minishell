/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/29 18:52:24 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(int fd_out)
{
	char *pwd;

	pwd = getcwd(NULL, 1024); // maxsize
	if (pwd == NULL)
		return (2);
	ft_putstr_fd(pwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(pwd);
	return (EXIT_SUCCESS);
}

char *find_path(char *str, t_env *env)
{
	int		i;
	t_env	*tmp;
	char	*new_path;
	char	**path_arr;
	struct stat s;

	tmp = find_env_from_env("PATH", env);
	path_arr = ft_split(tmp->value, ':');
	i = 0;
	DEBUG && printf("----------------"GREEN"FIND NEW_PATH"RESET"---------------\n");
	while(path_arr[i])
	{
		tmp->value = ft_strjoin("/", str);
		new_path = ft_strjoin(path_arr[i], tmp->value);
		free(tmp->value);
		free(tmp);
		DEBUG && printf("\tnew_path ["MAGENTA"%d"RESET"] : ["MAGENTA"%s"RESET"]\n", i, new_path);
		if (!stat(new_path, &s))
		{
			DEBUG && printf("--------------------------------------------\n");
			return (new_path);
		}
		free(new_path);
		i++;
	}
	DEBUG && printf("--------------------------------------------\n");
	return (ft_strdup(str));
}

void	exec_child_process(char *str, t_env *env)
{
	char *path;
	char *cmd[2];
	char **envp;
	int	cnt;

	DEBUG && printf("exec_child_process()\t"GREEN"START"RESET"\n");
	path = find_path(str, env);
	cmd[0] = str;
	cmd[1] = 0;

	cnt = env_count(env);
	envp = malloc(sizeof(char *) * (cnt + 1));
	env_to_envp(env, envp);
	execve(path, cmd, envp);

	free(path);
	free_envp(envp);
	free(envp);
	exit(1);
}

int	exec_fork(char *str, t_env *env)
{
	pid_t	pid;
	int		status;
	DEBUG && printf("exec_fork()\t\t"GREEN"START"RESET"\n");
	pid = fork();
	if (pid == 0)
	{
		exec_child_process(str, env);
		return(1);
	}
	waitpid(pid, &status, 0);
//	close(fd[1]);
//	close(fd[0]);
	return (1);
}

int extern_function(t_cmd_arg *ca)
{
	exec_fork(ca->argv[0], ca->env);
	return (EXIT_SUCCESS);
}

int builtin_function(t_cmd_arg *ca)
{
	if (ft_strncmp(ca->argv[0], "pwd", 4) == 0)
		ft_pwd(ca->fd[WRITE]);
	else if (!ft_strncmp(ca->argv[0], "exit", 5))
		builtin_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "echo", 5))
		builtin_echo(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "env", 4))
		builtin_env(ca->env);
	else if (!ft_strncmp(ca->argv[0], "export", 7))
		ft_export(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "unset", 6))
		builtin_unset(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "cd", 3))
		ft_cd(ca->argc, ca->argv, ca->env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute1(t_cmd_lst *cmds, t_env *env)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	return (EXIT_SUCCESS);
}

int	execute2(t_cmd_lst *cmds, t_env *env)
{
	return (0);
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
	else
	 	execute2(cmds, env);
	return (1);
}
