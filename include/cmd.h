/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:37:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 14:55:53 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "lst.h"
# include "env.h"

typedef struct s_cmd
{
	t_lst	*tokens;
	t_lst	*rd;
}			t_cmd;

typedef struct s_cmd_lst
{
	t_cmd				*cmd;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

typedef struct s_cmd_arg
{
	char	**argv;
	int		argc;
	int		fd_in;
	int		fd_out;
	t_env	*env;
}			t_cmd_arg;

/* cmd_arg */
int			print_cmd_arg(t_cmd_arg *cmd_arg);
char		**get_cmd_argv(t_lst *tokens);
t_cmd_arg	*parse_cmd_arg(t_cmd *cmd, t_env *env, int fd_in, int fd_out);

/* cmd_lst */
t_cmd_lst	*cmd_lst_new(t_cmd *cmd);
void		cmd_lst_clear(t_cmd_lst *head);
int			cmd_lst_size(t_cmd_lst *head);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *lst);
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);


#endif
