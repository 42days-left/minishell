/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/11/01 20:15:06 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *init_token(int type, char *arg)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0); //error check
	token->type = type;
	token->arg = arg;
	return (token);
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

int lexer(char **strs, t_lst *tokens)
{
	int	i;
	int	type;
	char *arg;

	i = 0;
	while(strs[i])
	{
		printf("strs[%d]: %s\n", i, strs[i]);
		type = get_type(strs[i]);
		if (type == PIPE)
			arg = 0;
		else if (type == WORD)
			arg = ft_strdup(strs[i]);
		else if (strs[i + 1] && get_type(strs[i + 1]) == WORD)
		{
			arg = ft_strdup(strs[i + 1]);
			i++;
		}
		else
			return (0); //error check pls here!
		lst_add_back_token(&tokens, init_token(type, arg));
		//type arg 값을 tokens리스트에 넣을 노드를 생성한다.
		printf("type: %d, arg: %s\n", type, arg);
		i++;
	}
	
//	t_token *sample;
//	while(i)
//	{
//		printf("-11-------");
//		sample = tokens->arg;
//		printf("type: %d, arg: %s\n", sample->type, sample->arg);
//		tokens = tokens->next;
//		i--;
//	}
	return(1);
}
