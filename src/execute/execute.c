/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/22 19:39:39 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_process2(t_cmd_arg *ca)
{
	char	*path;
	char	**envp;

	DEBUG && printf("exec_child_process()\t"GREEN"START"RESET"\n");
	if (ca->argc == 0)
		exit(0);
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
}

void	extern_function(t_cmd_arg *cmd_arg)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_dup(cmd_arg->fd_in, STDIN_FILENO);
		ft_dup(cmd_arg->fd_out, STDOUT_FILENO);
		exec_child_process2(cmd_arg);
		exit(0);
	}
	wait(&status);
	g_exitstat = get_wexitstat(status);
}

int	execute_single_cmd(t_cmd_lst *cmds, t_env *env, int fd_in, int fd_out)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env, fd_in, fd_out);
	if (!cmd_arg)
		return (EXIT_FAILURE);
	DEBUG && print_cmd_arg(cmd_arg);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	free_cmd_arg(cmd_arg);
	return (EXIT_SUCCESS);
}

int	execute_multi_cmds(t_cmd_lst *cmds, t_env *env, int fd_in, pid_t last_pid)
{
	t_cmd_lst	*curr;
	pid_t		pid;
	int			status;
	int			fd_out;
	int			pipe_fd[2];

	if (!cmds)
		return (wait_cmds(last_pid));
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
		fd_close(pipe_fd[READ]);
		execute_single_cmd(curr, env, fd_in, fd_out);
		exit(g_exitstat);
	}
	fd_close(fd_in);
	fd_close(fd_out);
	return (execute_multi_cmds(curr->next, env, pipe_fd[READ], pid));
}

void	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	on_signal();
	curr = cmds;
	count = cmd_lst_size(curr);
	if (count == 1)
		execute_single_cmd(cmds, env, STDIN_FILENO, STDOUT_FILENO);
	else
		execute_multi_cmds(cmds, env, STDIN_FILENO, -1);
}
