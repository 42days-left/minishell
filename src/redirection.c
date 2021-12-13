/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:28:28 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/13 14:40:27 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

# define	FD_IN	0
# define	FD_OUT	1


void	ft_close(int fd)
{
	if (fd == STDIN_FILENO)
		return ;
	if (fd == STDOUT_FILENO)
		return ;
	if (fd == STDERR_FILENO)
		return ;
	close(fd);
}

int	left_redir(char *file)
{
	return (open(file, O_RDONLY));
}

int	left_double_redir(char *fd)
{
	return (ft_atoi(fd));
}

/**
 * @brief 0644 : 권한 설정, 소유자는 읽기/쓰기가 가능하며, 나머지 모든 사람은 읽기만 가능.
 *
 * @param file
 * @return int
 */
int	right_redir(char *file)
{
	return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644));
}

int	right_double_redir(char *file)
{
	return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0644));
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
	// printf("get_fd start\n");
	while (node)
	{
		token = node->data;
		fd_type = get_fd_type(token->type);
		ft_close(fds[fd_type]);
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
