/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:51:46 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 16:52:07 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_remove_quote(char **str_ptr, char **buf_ptr)
{
	char	in_quote;

	in_quote = 0;
	while (**str_ptr != '\0')
	{
		if (in_quote == 0 && (**str_ptr == '\"' || **str_ptr == '\''))
		{
			in_quote = **str_ptr;
			(*str_ptr)++;
		}
		else if (**str_ptr == in_quote)
		{
			in_quote = 0;
			(*str_ptr)++;
		}
		else
			*(*buf_ptr)++ = *(*str_ptr)++;
	}
}

void	remove_quote_token(t_token *token)
{
	char	buf[BUF_SIZE];
	char	*str_ptr;
	char	*buf_ptr;

	if (token->type == PIPE)
		return ;
	str_ptr = token->word;
	buf_ptr = buf;
	_remove_quote(&str_ptr, &buf_ptr);
	*buf_ptr = '\0';
	free(token->word);
	token->word = ft_strdup(buf);
}
