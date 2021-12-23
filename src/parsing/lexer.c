/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/12/24 01:17:32 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *word)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit_err(EXIT_FAILURE, "Malloc Error");
	token->type = type;
	token->word = word;
	return (token);
}

static int	get_type(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (D_REDIR_L);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (D_REDIR_R);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR_L);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR_R);
	return (WORD);
}

int	lexer(char **strs, t_lst **tokens)
{
	int		type;
	char	*word;
	int		i;

	i = 0;
	while (strs[i])
	{
		type = get_type(strs[i]);
		if (type == PIPE)
			word = NULL;
		else if (type == WORD)
			word = ft_strdup(strs[i]);
		else if (strs[i + 1] && get_type(strs[i + 1]) == WORD)
			word = ft_strdup(strs[i++ + 1]);
		else
		{
			printf(YELLOW"lexer: syntax error near unexpected token `newline'\
			\n"RESET);
			return (EXIT_FAILURE);
		}
		lst_add_back(tokens, lst_new(init_token(type, word)));
		i++;
	}
	return (EXIT_SUCCESS);
}
