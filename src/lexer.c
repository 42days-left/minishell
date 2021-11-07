/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/11/06 22:39:26 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *init_token(int type, char *arg)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf(RED"INIT_TOKEN ERROR\n"RESET);
		return (0); //error check
	}
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
		{
			printf("LEXER ERR\n");
			return (0); //error check pls here!
		}
		//lst_add_back(&tokens, lst_new(init_token(type, arg)));
		lst_add_back_token(&tokens, init_token(type, arg));
		i++;
	}
	return(EXIT_SUCCESS);
}

int print_token(t_token *token)
{
	char  *type;

	if (token->type == PIPE)
		type = "PIPE";
	else if (token->type == COMMAND)
		type = "COMMAND";
	else if (token->type == WORD)
		type = "WORD";
	else if (token->type == REDIR_L)
		type = "REDIR_L '<'";
	else if (token->type == REDIR_R)
		type = "REDIR_R '>'";
	else if (token->type == D_REDIR_L)
		type = "D_REDIR_L '<<'";
	else if (token->type == D_REDIR_R)
		type = "D_REDIR_R '>>'";
	else
		type = "WTF?";
	printf("type: %s,\tvalue: %s\n", type, token->arg);
	return (1);
}


int print_token_list(t_lst *tokens)
{
	t_lst *node;

	if (tokens == NULL)
	{
		printf("TOKEN is "MAGENTA"NULL\n"RESET);
		return (0);
	}
	printf("--------------"GREEN"PRINT TOKEN LIST"RESET"--------------\n");
	//node = tokens;
	//printf ("1st node : [%s]", ((t_token *)(node->next->value))->arg);
	//while(node->next != NULL)
	node = tokens->next;
	while(node)
	{
		printf("HELLO!\n");
		print_token(node->value);
		node = node->next;
	}
	printf("--------------"GREEN"----------------"RESET"--------------\n");
	return (1);
}
