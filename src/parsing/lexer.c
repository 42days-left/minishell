/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/12/18 16:16:50 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *word)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		printf(RED"INIT_TOKEN ERROR\n"RESET);
		return (0); //error check
	}
	token->type = type;
	token->word = word;
	return (token);
}

int	get_type(char *str)
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
		{
			word = ft_strdup(strs[i + 1]);
			i++;
		}
		else
		{
			printf(RED"LEXER ERR\n"RESET);
			return (0); //error check pls here!
		}
		lst_add_back(tokens, lst_new(init_token(type, word)));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	print_token(t_token *token)
{
	char	*type;

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
		type = RED"WTF?"RESET;
	printf("type: ["MAGENTA"%s"RESET"],\tvalue: ["MAGENTA"%s"RESET"]\n", type, token->word);
	return (1);
}

int	print_token_list(t_lst *tokens)
{
	t_lst	*node;

	if (tokens == NULL)
	{
		printf("TOKEN is "MAGENTA"NULL\n"RESET);
		return (0);
	}
	printf("--------------"GREEN"PRINT LEXER TOKEN"RESET"-------------\n");
	node = tokens;
	while (node != NULL)
	{
		print_token(node->data);
		node = node->next;
	}
	printf("--------------------------------------------\n");
	return (1);
}
