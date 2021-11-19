/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/19 15:49:42 by yubae            ###   ########.fr       */
=======
/*   Updated: 2021/11/19 15:11:24 by jisokang         ###   ########.fr       */
>>>>>>> f99718e310c0e6be5427d1538fe28eae24436033
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "lst.h"

<<<<<<< HEAD
typedef struct	s_tmp
{
	char *str;
	int	 fd[2];
	struct s_tmp *next;
}				t_tmp;
=======
typedef struct	s_cmd
{
	t_lst	*args;
	t_lst	*rd;
	int		fd[2];		//어느게 나을려나?
	int		fd_in;		//어느게 나을려나?
	int		fd_out;
}			t_cmd;

int	parser(t_lst *tokens, t_lst *cmds);
>>>>>>> f99718e310c0e6be5427d1538fe28eae24436033

#endif
