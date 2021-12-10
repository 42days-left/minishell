/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/10 17:36:37 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_env *env)
{
	if (env == NULL)
		exit_err(2, "env err");
	print_envp_lst(env);
}

void	ft_close(int fd)
{
	if (fd == STDIN_FILENO)
		return ;
	if (fd == STDOUT_FILENO)
		return ;
	if (fd == STDERR_FILENO)
		return ;
	close(fd);
	printf("close :%d\n", fd);
}

int		ft_dup2(int oldfd, int newfd)
{
	int res;
	printf("dup2\n");
	if (oldfd == newfd)
		return (1);
	printf("%d, %d\n", oldfd, newfd);
	res = dup2(oldfd, newfd);
	printf("%d, %d\n", oldfd, newfd);
	printf("res: %d \n", res);
	ft_close(oldfd);
	return (res);
}

int	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	char	*home;
	t_env	*tmp;

	tmp = find_env_from_env("HOME", env);
	if (argc ==	1 && tmp)
		path = tmp->value;
	else if (argc == 1 && tmp == NULL)
	{
		printf("cd: HOME not set\n");
		return (2);
	}
	else if (argc == 2)
	{
		path = argv[1];
		if (path[0] == '~' && path[1] == 0)
			path = tmp->value;
	}
	if (chdir(path) == ERROR)
	{
			printf("cd: string not in pwd: %s\n", argv[1]);
			chdir(".");
			return (2);
	}
	return (EXIT_SUCCESS);
}

void	ft_exit(int argc, char **argv)
{
		(void)argc;
		(void)argv;
		printf("exit\n");
		exit(1);
}

int	ft_pwd(int fd_out)
{
	char *pwd;

	printf("pwd\n");
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
		//free(tmp);
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

void	exec_extern_process(char *str, t_env *env)
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

//int	exec_fork(char *str, t_env *env, int read, int write)
//{
//	pid_t	pid;
//	int		status;
//	DEBUG && printf("exec_fork()\t\t"GREEN"START"RESET"\n");
//	pid = fork();
//	if (pid == 0)
//	{
//		exec_child_process(str, env);
//		return(1);
//	}
//	waitpid(pid, &status, 0);
////	close(fd[1]);
////	close(fd[0]);
//	return (1);
//}

int extern_function(t_cmd_arg *ca, int read, int write)
{
	int	pid;
	int	status;
	printf("	extern_function in\n");
	printf("read:%d, write:%d\n", read, write);
	pid = fork();
	if (pid == 0)
	{
		//exec_fork(ca->argv[0], ca->env, read, write);
	//	ft_dup2(read, STDIN_FILENO);
	//	ft_dup2(write, STDOUT_FILENO);
		exec_extern_process(ca->argv[0], ca->env);
		return (1);
	}
	waitpid(pid, &status, 0);
	return (EXIT_SUCCESS);
}

int builtin_function(t_cmd_arg *ca, int read, int write)
{
	printf("builtin_func\n");
	if (ft_strncmp(ca->argv[0], "pwd", 4) == 0)
		ft_pwd(write);
	else if (!ft_strncmp(ca->argv[0], "exit", 5))
		ft_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "echo", 5))
		builtin_echo(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "env", 4))
		ft_env(ca->env);
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

int	execute1(t_cmd_lst *cmds, t_env *env, int read, int write)
{
	t_cmd_arg	*cmd_arg;

	printf("execute1 in\n");
	cmd_arg = parse_cmd_arg(cmds->cmd, env);
	//cmd_arg->fd[READ] = read;
	//cmd_arg->fd[WRITE] = write;
	ft_dup2(read, STDIN_FILENO);
	ft_dup2(write, STDOUT_FILENO);
	printf("read:%d, write: %d\n", read,  write);
	//printf("cmd_arg->fd[READ]: %d, cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[READ], cmd_arg->fd[WRITE]);
	set_signal();
	if (builtin_function(cmd_arg, read, write))
		extern_function(cmd_arg, read, write);
	return (EXIT_SUCCESS);
}

int	execute2(t_cmd_lst *cmds, t_env *env, int read, pid_t last_pid)
{
	t_cmd_lst	*curr;
	t_cmd_arg	*cmd_arg;
	pid_t	pid;
	int		status;
	int		write;
	
	if (!cmds->next)
		return(waitpid(last_pid, &status, 0));
	printf("\nexecute2 !!!!!!!!!!!!\n");
	curr = cmds;
	cmd_arg = parse_cmd_arg(curr->cmd, env);
	write = STDOUT_FILENO;
	if (curr->next)
	{
		printf("curr=>next\n");
		pipe(cmd_arg->fd);
		write = cmd_arg->fd[WRITE];
		printf("read:%d, write: %d\n", read,  write);
		printf("cmd_arg->fd[READ]: %d, cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[READ], cmd_arg->fd[WRITE]);
	}
	pid = fork();
	if (pid == 0)
	{
		off_signal();
		printf("child process\n");
		
		printf("read:%d, write: %d\n", read,  write);
		printf("cmd_arg->fd[READ]: %d, cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[READ], cmd_arg->fd[WRITE]);
		ft_close(cmd_arg->fd[READ]);
		execute1(curr, env, read, write);
		exit (1);
	}
	//ft_close(read);
	//ft_close(write);
	return (execute2(curr->next, env, cmd_arg->fd[READ], pid));
}



int	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	off_signal();
	curr = cmds;
	count = cmd_lst_size(curr);
	if (count == 1)
		execute1(cmds, env, STDIN_FILENO, STDOUT_FILENO);
	else
		execute2(cmds, env, STDIN_FILENO, -1);
	set_signal();
	return (1);
}
