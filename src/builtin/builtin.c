/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/14 14:41:13 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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


// static void	wait_process(t_cmd_arg *proc)
// {
// 	int	status;

// 	wait(&status);
// 	g_exitstat = WEXITSTATUS(status);
// 	// if (g_exit_code == ERR_EXECTUE_COMMAND_IS_DIRECTORY \
// 	// 	|| g_exit_code == ERR_EXECTUE_COMMAND_NOT_FOUND \
// 	// 	|| g_exit_code == ERR_EXECTUE_COMMAND_NO_FILE)
// 	// 	ft_error(g_exit_code, proc->argv[0]);
// 	// if (WIFSIGNALED(status))
// 	// 	g_exit_code = 128 + WTERMSIG(status);
// }

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
