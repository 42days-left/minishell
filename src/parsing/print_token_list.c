/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 00:52:20 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 01:20:20 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str_type(int type)
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
	return (type_str);
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
		return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
