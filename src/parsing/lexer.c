/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:13:02 by yubae             #+#    #+#             */
/*   Updated: 2021/12/22 16:05:09 by jisokang         ###   ########.fr       */
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
			word = ft_strdup(strs[i++ + 1]);
		else
		{
			printf(YELLOW\
			"lexer: syntax error near unexpected token `newline'\
			\n"RESET);
			return (EXIT_FAILURE);
		}
		lst_add_back(tokens, lst_new(init_token(type, word)));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*get_str_type(int type)
{
	char	*type_str;
	if (type == PIPE)
		type_str = "PIPE";
	else if (type == COMMAND)
		type_str = "COMMAND";
	else if (type == WORD)
		type_str = "WORD";
	else if (type == REDIR_L)
		type_str = "[ <]REDIR_L";
	else if (type == REDIR_R)
		type_str = "[ >]REDIR_R";
	else if (type == D_REDIR_L)
		type_str = "[<<]D_REDIR_L";
	else if (type == D_REDIR_R)
		type_str = "[>>]D_REDIR_R";
	else
		type_str = RED"UNKNOWN"RESET;
	return(type_str);
}

int	print_token(t_token *token)
{
	printf("{ type:["MAGENTA"%s"RESET"],\tvalue:["MAGENTA"%s"RESET"] }\n"\
	, get_str_type(token->type), token->word);
	return (1);
}

int	print_token_list(t_lst *tokens, char *title_str)
{
	t_lst	*node;

	if (tokens == NULL)
	{
		printf("TOKEN is "MAGENTA"NULL\n"RESET);
		return (0);
	}
	printf("["GREEN"%s"RESET"]\n{\n", title_str);
	node = tokens;
	while (node != NULL)
	{
		printf("\t");
		print_token(node->data);
		node = node->next;
	}
	printf("}\n");
	return (1);
}
