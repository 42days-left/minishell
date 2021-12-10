/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:26:01 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/10 17:08:18 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env, int fd_out)
{
	if (env == NULL)
		exit_err(2, "env err");
	print_envp_lst(env, fd_out);
	return (EXIT_SUCCESS);
}
