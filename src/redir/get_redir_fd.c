/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:11:07 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/16 13:16:54 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

# define	FD_IN	0
# define	FD_OUT	1

void	fd_close(int fd)
{
	if (fd == STDIN_FILENO)
		return ;
	if (fd == STDOUT_FILENO)
		return ;
	if (fd == STDERR_FILENO)
		return ;
	close(fd);
}

static int	get_fd_type(int type)
{
	if (type == REDIR_L || type == D_REDIR_L)
		return (FD_IN);
	return (FD_OUT);
}

int	get_redir_fd(t_lst *rds, int fds[2])
{
	int		fd_type;
	t_token	*token;
	t_lst	*node;

	node = rds;
	while (node)
	{
		token = node->data;
		fd_type = get_fd_type(token->type);
		fd_close(fds[fd_type]);
		if (token->type == REDIR_L)
			fds[fd_type] = left_redir(token->word);
		else if (token->type == D_REDIR_L)
			fds[fd_type] = left_double_redir(token->word);
		else if (token->type == REDIR_R)
			fds[fd_type] = right_redir(token->word);
		else if (token->type == D_REDIR_R)
			fds[fd_type] = right_double_redir(token->word);
		if (fds[fd_type] == -1)
			return (0);
		node = node->next;
	}
	return (1);
}
