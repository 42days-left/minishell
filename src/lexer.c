/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/10/31 19:18:12 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int lexer(char **strs, t_lst *tokens)
{
	int	i;
	int	type;
	char *value;

	i = 0;
	while(strs[i])
	{
		type = get_type(strs[i]);
		if (type = PIPE)
			value = 0;
		else if (type == WORD)
			value = ft_strdup(strs[i]);
		else if (strs[i + 1] && get_type(strs[i + 1] == WORD))
		{
			value = ft_strdup(strs[i + 1]);
			i++;
		}
		else
			return (0); //error check pls here!
		//lst_add_back(tokens, lst()) ->  type value 값을 tokens리스트에 넣을 노드를 생성한다.
	}
		return(1);
	}
}

int get_type(char *str)
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
