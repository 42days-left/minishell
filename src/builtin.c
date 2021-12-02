/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/02 17:58:04 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(t_cmd *cmd, t_env *env)
{
	if (((t_token *)cmd->tokens->next) == NULL)
		print_envp_lst(env);
}

void	ft_env(t_env *env)
{
	if (env == NULL)
		exit_err(2, "env err");
	print_envp_lst(env);
}

void	ft_echo(t_lst *cmds)
{
	return ;
}

void	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	char	*home;

	home = find_value_from_env("$HOME", env);
	if (argc ==	1)
		path = home;
	else if (argc == 2)
	{
		path = argv[1];
		if (path[0] == '~' && path[1] == 0)
			path = home;
	}
	if (chdir(path) == -1)
	{
			printf("cd: string not in pwd: %s\n", argv[1]);
			chdir(".");
	}
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
		printf("new_path %d: %s\n", i, new_path);
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
		i++;
	}
	return (ft_strdup(str));
}

void	exec_child_process(char *str, t_env *env)
{
	char *path;
	char *cmd[2];
	char **envp;
	int	cnt;

	printf("exec_child_process\n");
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

int		exec_fork(char *str, t_env *env)
{
	pid_t	pid;
	int		status;
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
	return (1);
}

int extern_function(t_cmd_arg *ca)
{
	exec_fork(ca->argv[0], ca->env);
	return (EXIT_SUCCESS);
}

int builtin_function(t_cmd_arg *ca)
{
	int	len;

	len = ft_strlen(ca->argv[0]);
	if (!ft_strncmp(ca->argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(ca->argv[0], "exit", 5))
		ft_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "env", 4))
		ft_env(ca->env);
	else if (!ft_strncmp(ca->argv[0], "cd", 3))
		ft_cd(ca->argc, ca->argv, ca->env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute1(t_cmd_lst *cmds, t_env *env, int read, int write)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env);
	//cmd_arg->fd[READ] = read;
	//cmd_arg->fd[WRITE] = write;
	dup2(read, cmd_arg->fd[READ]);
	dup2(write, cmd_arg->fd[WRITE]);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	return (EXIT_SUCCESS);
}

int	execute2(t_cmd_lst *cmds, t_env *env, int read, pid_t last_pid)
{
	t_cmd_lst	*curr;
	t_cmd_arg	*cmd_arg;
	pid_t	pid;
	int		status;
	int		write;
	
	printf("execute2 !!!!!!!!!!!!\n");
	curr = cmds;
	cmd_arg = parse_cmd_arg(curr->cmd, env);
	write = STDOUT_FILENO;
	printf("write1: %d\n", write);
	if (curr->next)
	{
		printf("curr=>next\n");
		pipe(cmd_arg->fd);
		write = cmd_arg->fd[READ];
		printf("write: %d\n", write);
	}
	pid = fork();
	if (pid == 0)
	{
		//off_signal();
		printf("child process\n");
		printf("cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[WRITE]);
		close(cmd_arg->fd[WRITE]);
		execute1(curr, env, read, write);
		return(1);
	}
	close(read);
	close(write);
	waitpid(pid, &status, 0);
	return (execute2(curr->next, env, cmd_arg->fd[WRITE], pid));
}



int	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	off_signal();
	curr = cmds;
	count = cmd_lst_size(curr);
	printf("################%d\n", count);
	if (count == 1)
		execute1(cmds, env, STDIN_FILENO, STDOUT_FILENO);
	else
		execute2(cmds, env, STDIN_FILENO, -1);
	set_signal();
	return (1);
}
