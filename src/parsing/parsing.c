/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:19:36 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/20 14:25:22 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_parse(t_lst *head)
{
	t_lst	*curr;
	t_lst	*next;
	t_token	*token;

	curr = head;
	if (!curr)
		return ;
	while (curr != NULL)
	{
		next = curr->next;
		token = (t_token *)curr->data;
		if (token)
		{
			if (token->word)
				free(token->word);
			free(token);
		}
		free(curr);
		curr = next;
	}
	head = NULL;
}

int	parse(char *script, t_env *env, t_cmd_lst **cmds)
{
	t_lst	*tokens;
	char	**strs;

	DEBUG && printf(GRAY"script = \"%s\"\n"RESET, script);
	if (tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = NULL;
	if (lexer(strs, &tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	DEBUG && print_token_list(tokens);
	replace(tokens, env);
	DEBUG && print_token_list(tokens);
	if (here_doc(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parser(tokens, cmds);
	free_strings(strs);
	// ft_lstclear2(&tokens, free_token_without_close);
	free_tokens_parse(tokens);
	// free(tokens);
	DEBUG && printf("["GREEN"PARSE DONE"RESET"]\n");
	return (EXIT_SUCCESS);
}
