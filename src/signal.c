/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:11:14 by yubae             #+#    #+#             */
/*   Updated: 2021/12/22 16:51:12 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern void	rl_replace_line(const char *text, int clear_undo);

void	signal_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		if (sig == SIGINT)
			printf("^C\n");
		if (sig == SIGQUIT)
			printf("^\\Quit:3\n");
	}
	g_exitstat = 1;
}

void	on_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	default_signal(void)
{
	off_echoctl();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	off_echoctl(void)
{
	struct termios	new_term;

	tcgetattr(STDOUT_FILENO, &new_term);
	new_term.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &new_term);
}
