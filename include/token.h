/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:58:18 by yubae             #+#    #+#             */
/*   Updated: 2021/11/07 23:28:30 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lst.h"

typedef struct	s_token
{
	int			type;
	char		*arg;
}				t_token;

t_token	*init_token(int type, char *arg);
//int		lexer(char **strs, t_lst *tokens);
int		lexer(char **strs, t_lst **tokens);
void	lst_add_back_token(t_lst **lst, t_token *new);
int		print_token(t_token *token);
int		print_token_list(t_lst *tokens);

#endif
