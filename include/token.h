/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:58:18 by yubae             #+#    #+#             */
/*   Updated: 2021/11/04 15:50:57 by jisokang         ###   ########.fr       */
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

int		lexer(char **strs, t_lst *tokens);
void	lst_add_back_token(t_lst **lst, t_token *new);
int		print_token(t_token *token);
int		print_token_list(t_lst *tokens);

#endif
