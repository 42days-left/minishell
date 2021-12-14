/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:11:09 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 14:41:57 by jisokang         ###   ########.fr       */
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
	free(path);
	free_envp(envp);
	exit(42);
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
	fd_close(fd1);
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
		ft_dup(cmd_arg->fd_in, STDIN_FILENO);
		ft_dup(cmd_arg->fd_out, STDOUT_FILENO);
		exec_child_process2(cmd_arg);
		// exit();
	}
	waitpid(pid, &status, 0);
	// wait(&status);
	g_exitstat = get_wexitstat(status);

	return (EXIT_SUCCESS);
}

int extern_function(t_cmd_arg *ca)
{
	exec_fork2(ca);
	free_cmd_arg(ca);
	return (EXIT_SUCCESS);
}

int	execute_single_cmd(t_cmd_lst *cmds, t_env *env, int fd_in, int fd_out)
{
	t_cmd_arg	*cmd_arg;
	cmd_arg = parse_cmd_arg(cmds->cmd, env, fd_in, fd_out);
	DEBUG && print_cmd_arg(cmd_arg);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	return (EXIT_SUCCESS);
}

int	wait_cmds(int last_pid)
{
	int status;
	waitpid(last_pid, &status, 0);
	WEXITSTATUS(status);
	while (wait(&status) != -1)
		;
	return (1);
}

int	execute_multi_cmds(t_cmd_lst *cmds, t_env *env, int fd_in, pid_t last_pid)
{
	t_cmd_lst	*curr;
	pid_t	pid;
	int		status;
	int		fd_out;
	int		pipe_fd[2];

	if (!cmds)
		return(wait_cmds(last_pid));
	curr = cmds;
	fd_out = STDOUT_FILENO;
	if (curr->next)
	{
		pipe(pipe_fd);
		fd_out = pipe_fd[WRITE];
	}
	pid = fork();
	if (pid == 0)
	{
		off_signal();
		fd_close(pipe_fd[READ]);
		exit(execute_single_cmd(curr, env, fd_in, fd_out));
	}
	waitpid(pid, &status, 0);
	fd_close(fd_in);
	fd_close(fd_out);
	return (execute_multi_cmds(curr->next, env, pipe_fd[READ], pid));
}

int	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	off_signal();
	curr = cmds;
	count = cmd_lst_size(curr);
	if (count == 1)
		execute_single_cmd(cmds, env, STDIN_FILENO, STDOUT_FILENO);
	else
		execute_multi_cmds(cmds, env, STDIN_FILENO, -1);
	set_signal();
	return (1);
}
