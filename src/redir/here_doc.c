/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:22:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 13:01:00 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define	PIPE_OUT	0
#define	PIPE_IN		1

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\b\b  \b\b\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exitstat = 1;
}

static void	sigint_handler_in_heredoc(int sig)
{
	(void)sig;
	printf("\b\b  \b\b\n");
	exit(1);
}

int	make_here_doc(char *end_str)
{
	int		status;
	int		pipe_fd[2];
	char	*str;

	printf("end_str : [%s]\n", end_str);
	pipe(pipe_fd);
	// signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		fd_close(pipe_fd[PIPE_OUT]);
		// signal(SIGINT, sigint_handler_in_heredoc);
		printf("pipe_fd[PIPE_IN] = ["BLUE"%d"RESET"]\n", pipe_fd[PIPE_IN]);
		printf("pipe_fd[PIPE_OUT] = ["BLUE"%d"RESET"]\n", pipe_fd[PIPE_OUT]);
		while (1)
		{
			str = readline("> ");
			// printf("input : [%s]\n", str);
			if (!str)
			{
				printf("NO LINE\n");
				exit(0);
			}
			if (ft_strncmp(str, end_str, ft_strlen(end_str) + 1) == 0)
			{
				printf("SAME LINE\n");
				exit(0);
			}
			// ft_putstr_fd(line, pipe_fd[PIPE_IN]);
			write(pipe_fd[PIPE_IN], str, ft_strlen(str));
			write(pipe_fd[PIPE_IN], "\n", 1);
			free (str);
			// printf("WHILE END\n");
		}
		// write(1, "HELLO WORLD!\n", 14);

	}
	fd_close(pipe_fd[PIPE_OUT]);
	wait(&status);
	// signal(SIGINT, sigint_handler);
	if (WEXITSTATUS(status) == 1)
		return (-1);
	return (pipe_fd[PIPE_OUT]);
}

int	here_doc(t_lst *tokens)
{
	t_lst	*curr;
	t_token	*token;
	int		fd;

	curr = tokens;
	while (curr)
	{
		token = curr->data;
		curr = curr->next;
		if (token->type == D_REDIR_L)
		{
			printf(RED"!HERE_DOC!\n"RESET);
			fd = make_here_doc(token->word);
			if (fd == -1)
			{
				printf(RED"FD ERR\n"RESET);
				return (EXIT_FAILURE);
			}
			free(token->word);
			token->word = ft_itoa(fd);
			printf("heredoc fd : [%s]\n", token->word);
		}
	}
	return (EXIT_SUCCESS);
}
