/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:28:28 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 20:12:21 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int	left_redir(char *file)
{
	if (!file)
		return(ERROR);
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
	if (!file)
		return(ERROR);
	return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644));
}

int	right_double_redir(char *file)
{
	if (!file)
		return(ERROR);
	return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0644));
}


