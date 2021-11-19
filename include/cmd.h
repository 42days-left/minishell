/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/19 15:49:42 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

//typedef struct	s_cmd
//{
//	t_lst	*args;
//	t_lst	*rd;
//}			t_cmd;

typedef struct	s_tmp
{
	char *str;
	int	 fd[2];
	struct s_tmp *next;
}				t_tmp;

#endif
