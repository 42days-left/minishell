/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:12:05 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/25 15:22:11 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LST_H
# define CMD_LST_H

# include "cmd.h"

typedef struct s_cmd_lst
{
	t_cmd				*cmd;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

t_cmd_lst	*cmd_lst_new(t_cmd *cmd);
void		cmd_lst_clear(t_cmd_lst *head);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *lst);
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);

#endif
