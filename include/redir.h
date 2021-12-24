/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:24:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 14:54:25 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "lst.h"

/* get_redir_fd */
void	fd_close(int fd);
int		get_redir_fd(t_lst *tokens, int fds[2]);

/* here_doc */
int		here_doc(t_lst *tokens);

/* redirection */
int		left_redir(char *file);
int		left_double_redir(char *fd);
int		right_redir(char *file);
int		right_double_redir(char *file);


#endif
