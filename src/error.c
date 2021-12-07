/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:24 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/07 21:00:00 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_err(int num, char *msg)
{
	g_exitstat = num;
	printf(BLUE"[[%d]] = [[%d]]\n"RESET, g_exitstat, num);
	printf(YELLOW"%s\n"RESET, msg);
	exit (g_exitstat);
}
