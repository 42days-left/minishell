/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/12/18 22:43:24 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_function(t_cmd_arg *ca)
{
	if (ca->argc == 0)
		return (EXIT_FAILURE);
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
