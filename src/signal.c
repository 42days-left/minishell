/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:11:14 by yubae             #+#    #+#             */
/*   Updated: 2021/11/29 15:26:15 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern void rl_replace_line (const char *text, int clear_undo);

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\b\b  \b\b\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("\b\b  \b\b");
	}
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
