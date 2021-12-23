/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:22:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 01:38:46 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PIPE_OUT	0
#define PIPE_IN		1

void	signal_handler_heredoc(int sig)
{
	printf("\n");
	exit(1);
}

static void	here_doc_loop(char *str, char *end_str, int	*pipe_fd)
{
	while (TRUE)
	{
		str = readline("> ");
		if (!str || !ft_strncmp(str, end_str, ft_strlen(end_str) + 1))
			exit(0);
		ft_putstr_fd(str, pipe_fd[PIPE_IN]);
		ft_putstr_fd("\n", pipe_fd[PIPE_IN]);
		free (str);
	}
}

static int	make_here_doc(char *end_str)
{
	int		status;
	int		pipe_fd[2];
	char	*str;

	pipe(pipe_fd);
	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		fd_close(pipe_fd[PIPE_OUT]);
		signal(SIGINT, signal_handler_heredoc);
		here_doc_loop(str, end_str, pipe_fd);
	}
	fd_close(pipe_fd[PIPE_IN]);
	wait(&status);
	signal(SIGINT, signal_handler_heredoc);
	if (get_wexitstat(status) == 1)
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
		if (token->type == D_REDIR_L)
		{
			fd = make_here_doc(token->word);
			if (fd == -1)
			{
				g_exitstat = EXIT_FAILURE;
				return (EXIT_FAILURE);
			}
			free(token->word);
			token->word = ft_itoa(fd);
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
