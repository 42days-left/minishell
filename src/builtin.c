/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/13 14:03:19 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_signal_handler
{
	void	(*sigint)();
	void	(*sigquit)();
}	t_signal_handler;

t_signal_handler	*sig_handler(void)
{
	static t_signal_handler	signals;

	return (&signals);
}



void	check_dot_path(char *path)
{
	if (path[0] == '.')
	{
		if (path[1] == '\0')
			exit_err(EXIT_SYNTAXERR, ".: filename argument required");
		else if (path[1] == '.' && path[2] == '\0')
			exit_err(EXIT_WRONGPATH, "..: command not found");
	}
}

char *find_path(char *in_path, t_env *env)
{
	int		i;
	t_env	*tmp;
	char	*new_path;
	char	**path_arr;
	struct stat s;

	tmp = find_env_from_env("PATH", env);
	path_arr = ft_split(tmp->value, ':');
	DEBUG && printf("----------------"GREEN"FIND NEW_PATH"RESET"---------------\n");
	if (!stat(in_path, &s))
	{
		check_dot_path(in_path);
		if ((s.st_mode & S_IFMT) == S_IFDIR)
		{
			printf(YELLOW"%s: "RESET, in_path);
			exit_err(EXIT_EXCUTE, "is a directory");
		}
		return(in_path);
	}
	if (in_path[0] == '/')
	{
		printf(YELLOW"%s: "RESET, in_path);
		exit_err(EXIT_WRONGPATH, "No such file or directory");
	}
	i = 0;
	while(path_arr[i])
	{
		tmp->value = ft_strjoin("/", in_path);
		new_path = ft_strjoin(path_arr[i], tmp->value);
		free(tmp->value);
		//free(tmp);
		DEBUG && printf("\tnew_path ["MAGENTA"%d"RESET"] : ["MAGENTA"%s"RESET"]\n", i, new_path);
		if (!stat(new_path, &s))
		{
			DEBUG && printf("-----------------------------------FIND_"GREEN"DONE"RESET"\n");
			return (new_path);
		}
		free(new_path);
		i++;
	}
	DEBUG && printf("-----------------------------------FIND_"RED"FAIL"RESET"\n");
	return (NULL);
}

static void	free_proc(t_cmd_arg *ca)
{
	free_strings(ca->argv);
	ft_close(ca->fd_in);
	ft_close(ca->fd_out);
	free(ca);
}

// int	exec_child_process2(t_cmd_arg *ca)
void	exec_child_process2(t_cmd_arg *ca)
{
	char *path;
	char **envp;

	if (ca->argc == 0)
		exit(0);
	DEBUG && printf("exec_child_process()\t"GREEN"START"RESET"\n");
	envp = env_to_envp(ca->env);
	path = find_path(ca->argv[0], ca->env);
	if (path != NULL)
		execve(path, ca->argv, envp);
	else
	{
		printf(YELLOW"%s"RESET, ca->argv[0]);
		exit_err(EXIT_WRONGPATH, ": command not found");
	}
	// printf(YELLOW"????\n"RESET);
	free(path);
	free_envp(envp);
	exit(42);
	// return(1);
}

/**
 * @brief Get the WEXITSTATUS object
 *
 * @param stat
 * @return int
 */
static int	get_wexitstat(int stat)
{
	return ((((*(int *)&(stat)) >> 8) & 0x000000ff));
}


int	ft_dup(int fd1, int fd2)
{
	int	rt;

	if (fd1 == fd2)
		return (1);
	rt = dup2(fd1, fd2);
	ft_close(fd1);
	return (rt);
}


int	exec_fork2(t_cmd_arg *cmd_arg)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_handler()->sigint);
		signal(SIGQUIT, sig_handler()->sigquit);
		// ft_dup(cmd_arg->fd[WRITE], STDIN_FILENO);
		// ft_dup(cmd_arg->fd[READ], STDOUT_FILENO);
		ft_dup(cmd_arg->fd_in, STDIN_FILENO);
		ft_dup(cmd_arg->fd_out, STDOUT_FILENO);
		exec_child_process2(cmd_arg);
		// exit();
	}
	// waitpid(pid, &status, 0);
	wait(&status);
	g_exitstat = get_wexitstat(status);

	return (EXIT_SUCCESS);
}

int extern_function(t_cmd_arg *ca)
{
	exec_fork2(ca);
	free_proc(ca);
	return (EXIT_SUCCESS);
}

int builtin_function(t_cmd_arg *ca)
{
	if (!ft_strncmp(ca->argv[0], "pwd", 4))
		g_exitstat = builtin_pwd(ca->fd_out);
	else if (!ft_strncmp(ca->argv[0], "exit", 5))
		g_exitstat = builtin_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "echo", 5))
		g_exitstat = builtin_echo(ca->argc, ca->argv, ca->fd_out);
	else if (!ft_strncmp(ca->argv[0], "env", 4))
		g_exitstat = builtin_env(ca->env, ca->fd_out);
	else if (!ft_strncmp(ca->argv[0], "export", 7))
		g_exitstat = builtin_export(ca->argc, ca->argv, ca->env, ca->fd_out);
	else if (!ft_strncmp(ca->argv[0], "unset", 6))
		g_exitstat = builtin_unset(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "cd", 3))
		g_exitstat = builtin_cd(ca->argc, ca->argv, ca->env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


static void	wait_process(t_cmd_arg *proc)
{
	int	status;

	wait(&status);
	g_exitstat = WEXITSTATUS(status);
	// if (g_exit_code == ERR_EXECTUE_COMMAND_IS_DIRECTORY \
	// 	|| g_exit_code == ERR_EXECTUE_COMMAND_NOT_FOUND \
	// 	|| g_exit_code == ERR_EXECTUE_COMMAND_NO_FILE)
	// 	ft_error(g_exit_code, proc->argv[0]);
	// if (WIFSIGNALED(status))
	// 	g_exit_code = 128 + WTERMSIG(status);
}

// void	execute_extern(t_cmd_arg *ca)
// {
// 	// printf("in execute_extern()\n");
// 	if (fork() == 0)
// 	{
// 		signal(SIGINT, sig_handler()->sigint);
// 		signal(SIGQUIT, sig_handler()->sigquit);
// 		ft_dup(ca->fd[WRITE], STDIN_FILENO);
// 		ft_dup(ca->fd[READ], STDOUT_FILENO);
// 		exit(extern_function(ca));
// 	}
// 	wait_process(ca);
// }

int	execute1(t_cmd_lst *cmds, t_env *env, int fd_in, int fd_out)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env, fd_in, fd_out);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	return (EXIT_SUCCESS);
}



int	execute2(t_cmd_lst *cmds, t_env *env, int fd_in, pid_t last_pid)
{
	t_cmd_lst	*curr;
	t_cmd_arg	*cmd_arg;
	pid_t	pid;
	int		status;
	int		fd_out;
	int		pipe_fd[2];

	if (!cmds->next)
		return(waitpid(last_pid,&status, 0));
	printf("\nexecute2 !!!!!!!!!!!!\n");
	curr = cmds;
	// cmd_arg = parse_cmd_arg(curr->cmd, env, fd_in, );
	fd_out = STDOUT_FILENO;
	if (curr)
	{
		pipe(pipe_fd);
		fd_out = pipe_fd[READ];
		// printf("read:%d, write: %d\n", read,  write);
		// printf("cmd_arg->fd[READ]: %d, cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[READ], cmd_arg->fd[WRITE]);
//		pipe(fd);
//		write = fd[WRITE];
	}
	pid = fork();
	if (pid == 0)
	{
		off_signal();
		// printf("child process\n");
		// printf("read:%d, write: %d\n", read,  write);
		// printf("cmd_arg->fd[READ]: %d, cmd_arg->fd[WRiTE] : %d\n", cmd_arg->fd[READ], cmd_arg->fd[WRITE]);
		ft_close(cmd_arg->fd_in);
		//		ft_close(fd[READ]);
		exit(execute1(curr, env, fd_in, fd_out));
		//exit (1);
	}
	waitpid(pid, &status, 0);
	ft_close(fd_in);
	ft_close(fd_out);
	return (execute2(curr->next, env, cmd_arg->fd_in, pid));
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
