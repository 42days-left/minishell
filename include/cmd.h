/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/21 14:43:00 by jisokang         ###   ########.fr       */
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
	int		num;
}			t_cmd;

int	parser(t_lst *tokens, t_lst **cmds);
int	print_cmds_list(t_lst *cmds);

#endif
