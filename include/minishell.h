/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/31 18:37:42 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* readline함수를 사용하기위한 헤더 */
# include <readline/readline.h>

/* add_history함수를 사용하기위한 헤더 */
# include <readline/history.h>

/* printf함수를 사용하기위한 헤더 */
# include <stdio.h>

/* free함수를 사용하기위한 헤더 */
# include <stdlib.h>

# include "color.h"
# include "../lib/include/libft.h"

/* TYPE */
# define	SCRIPT	0
# define	COMMAND	1
# define	WORD	2
# define	PIPE	3
# define	REDIR_L 4
# define	REDIR_R 5
# define	D_REDIR_L 6
# define	D_REDIR_R 7

typedef struct s_lst
{
	void			*value;
	struct s_lst	*next;
}					t_lst;

t_lst	*lst_new(void *value);
void	lst_insert(t_lst *before, t_lst *new);
void	lst_add_front(t_lst **lst, t_lst *new);
void	lst_add_back(t_lst **lst, t_lst *new);
void	print_lst_nul(t_lst *head);

#endif


