/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/25 20:58:11 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "lst.h"
# include "env.h"

typedef struct	s_cmd
{
	t_lst	*args;
	t_lst	*rd;
	int		fd[2];		//어느게 나을려나?
	int		num;
}			t_cmd;

typedef struct s_cmd_lst
{
	t_cmd				*cmd;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

typedef struct s_cmd_arg
{
	int		argc;
	int		fd_in;
	char	**argv;
	int		fd_out;
	//t_env	*env;
}			t_cmd_arg;

t_cmd_lst	*cmd_lst_new(t_cmd *cmd);
void		cmd_lst_clear(t_cmd_lst *head);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *lst);
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);

int	parser(t_lst *tokens, t_cmd_lst **cmds);
int	print_cmds_list(t_cmd_lst *cmds);

#endif
