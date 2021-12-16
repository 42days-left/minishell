/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:24:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/16 13:18:05 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "lst.h"


void	fd_close(int fd);
int		get_redir_fd(t_lst *tokens, int fds[2]);

int		left_redir(char *file);
int		left_double_redir(char *fd);
int		right_redir(char *file);
int		right_double_redir(char *file);

#endif
