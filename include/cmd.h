/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/02 15:39:49 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

typedef struct	s_cmd
{
	t_lst	*args;
	t_lst	*rd;
}			t_cmd;


#endif
