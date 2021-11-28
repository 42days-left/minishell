/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devleo <devleo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:58:18 by yubae             #+#    #+#             */
/*   Updated: 2021/11/28 16:39:10 by devleo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lst.h"

typedef struct	s_token
{
	int			type;
	char		*word;
	// char		*arg;
}				t_token;

t_token	*init_token(int type, char *word);
//int		lexer(char **strs, t_lst *tokens);
int		lexer(char **strs, t_lst **tokens);
void	lst_add_back_token(t_lst **lst, t_token *new);
int		print_token(t_token *token);
int		print_token_list(t_lst *tokens);

#endif
