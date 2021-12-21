/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:09:53 by yubae             #+#    #+#             */
/*   Updated: 2021/12/22 00:37:56 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the WEXITSTATUS object
 *
 * @param stat
 * @return int
 */

int	get_wexitstat(int stat)
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

int	wait_cmds(int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	g_exitstat = get_wexitstat(status);
	while (wait(&status) != -1)
		;
	return (1);
}
