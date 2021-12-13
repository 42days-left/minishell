/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:11:14 by yubae             #+#    #+#             */
/*   Updated: 2021/12/13 20:37:11 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern void rl_replace_line (const char *text, int clear_undo);

void	signal_handler(int sig)
{
	pid_t pid;
	int		status;

//	pid = -1;
	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			printf("\b\b\b\b\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			printf("\n");
	}
	if (sig == SIGQUIT)
	{
		if (pid == -1)
			printf("\b\b\b\b");
		else
			printf("Quit: 3\n");
	}
}

//void	set_signal(void)
//{
//	signal(SIGINT, signal_handler);
//	signal(SIGQUIT, signal_handler);
//}

//void	on_signal_handler(int sig)
//{
//	if (sig == SIGINT)
//	{
//		rl_replace_line("", 0);
//		rl_on_new_line();
//		printf("\n");
//	}
//	if (sig == SIGQUIT)
//	{
//		printf("Quit: 3");
//		printf("\n");
//	}
//	set_signal();
////}

void	on_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	off_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
