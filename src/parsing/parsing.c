/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:19:36 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/22 16:09:31 by jisokang         ###   ########.fr       */
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
	DEBUG && print_token_list(tokens, "LEXER TOKENS");
	replace(tokens, env);
	DEBUG && print_token_list(tokens, "REPLACE TOKENS");
	if (here_doc(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parser(tokens, cmds);
	free_strings(strs);
	free_tokens_parse(tokens);
	DEBUG && printf("🐚 parsing...\t["GREEN"done"RESET"]\n");
	return (EXIT_SUCCESS);
}
