/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:22:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/17 17:33:34 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define	PIPE_OUT	0
#define	PIPE_IN		1

static void	sigint_handler_hd(int sig)
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
	char	*line;

	printf("end_str : [%s]\n", end_str);
	pipe(pipe_fd);
	if (fork() == 0)
	{
		fd_close(pipe_fd[PIPE_OUT]);
		signal(SIGINT, sigint_handler_in_heredoc);
		while (TRUE)
		{
			line = readline(">");
			// printf("WHILE START\n");
			if (!line)
			{
				printf("NO LINE\n");
				exit(0);
			}
			// printf("after no lien\n");
			if (ft_strncmp(line, end_str, ft_strlen(end_str) + 1) == 0)
			{
				printf("SAME LINE\n");
				exit(0);
			}
			// printf("afte same line\n");
			// ft_putstr_fd(line, pipe_fd[PIPE_IN]);
			// ft_putstr_fd("\n", pipe_fd[PIPE_IN]);
			write(pipe_fd[PIPE_IN], line, ft_strlen(line));
			write(pipe_fd[PIPE_IN], "\n", 1);
			// printf("afte write line\n");
			free (line);
			// printf("WHILE END\n");
		}

	}
	fd_close(pipe_fd[PIPE_OUT]);
	wait(&status);
	signal(SIGINT, sigint_handler_hd);
	// printf("HERE DOC OUT\n");
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
		if (token->type == D_REDIR_L)
		{
			printf(RED"!HERE_DOC!\n"RESET);
			fd = make_here_doc(token->word);
			free(token->word);
			token->word = ft_itoa(fd);
		}
		curr = curr->next;
	}
	return (TRUE);
}
