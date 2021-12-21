/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:22:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 15:58:11 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define	PIPE_OUT	0
#define	PIPE_IN		1

void signal_handler_heredoc(int sig)
{
	printf("\n");
	exit(1);
}

int	make_here_doc(char *end_str)
{
	int		status;
	int		pipe_fd[2];
	char	*str;

	DEBUG && printf("----------------"GREEN"HERE DOCUMENT"RESET"---------------\n");
	DEBUG && printf("end_str : ["BLUE"%s"RESET"]\n", end_str);
	signal(SIGINT, SIG_IGN);
	pipe(pipe_fd);
	if (fork() == 0)
	{
		signal(SIGINT, signal_handler_heredoc);
		fd_close(pipe_fd[PIPE_OUT]);
		DEBUG && printf("pipe_fd[PIPE_IN]:  ["BLUE"%d"RESET"]\n", pipe_fd[PIPE_IN]);
		DEBUG && printf("pipe_fd[PIPE_OUT]: ["BLUE"%d"RESET"]\n", pipe_fd[PIPE_OUT]);
		DEBUG && printf("--------------------------------------------\n");
		while (TRUE)
		{
			str = readline("> ");
			if (!str)
				exit(0);
			if (ft_strncmp(str, end_str, ft_strlen(end_str) + 1) == 0)
				exit(0);
			ft_putstr_fd(str, pipe_fd[PIPE_IN]);
			ft_putstr_fd("\n", pipe_fd[PIPE_IN]);
			free (str);
		}
	}
	fd_close(pipe_fd[PIPE_IN]);
	wait(&status);
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
				printf(RED"FD ERR\n"RESET);
				return (EXIT_FAILURE);
			}
			free(token->word);
			token->word = ft_itoa(fd);
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
