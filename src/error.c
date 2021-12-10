/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:24 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/10 13:23:29 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_err(int num, char *msg)
{
	g_exitstat = num;
	DEBUG && printf(BLUE"[g_exitstat[%d]] = [num[%d]]\n"RESET, g_exitstat, num);
	printf(YELLOW"%s\n"RESET, msg);
	exit (g_exitstat);
}
