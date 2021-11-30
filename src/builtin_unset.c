/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:02:58 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/30 19:22:33 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	remove_env_var(int argc, char **argv, t_env *env)
{
	return (0);
}

int	builtin_unset(int argc, char **argv, t_env *env)
{
	if (argc == 1)
		return (1);
	remove_env_var(argc, argv, env);
	return (EXIT_SUCCESS);
}
