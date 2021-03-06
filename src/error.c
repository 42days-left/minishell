/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:24 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 20:48:40 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_err(int num, char *msg)
{
	g_exitstat = num;
	printf(YELLOW"%s\n"RESET, msg);
	exit (g_exitstat);
}
