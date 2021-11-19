/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/19 19:01:05 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "lst.h"

typedef struct	s_cmd
{
	t_lst	*args;
	t_lst	*rd;
	int		fd[2];		//어느게 나을려나?
	int		fd_in;		//어느게 나을려나?
	int		fd_out;
}			t_cmd;

int	parser(t_lst *tokens, t_lst **cmds);
int	print_cmds_list(t_lst *cmds);

#endif
