/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:19:36 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/17 21:05:50 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @param script string entered at the prompt
 */
int	parse(char *script, t_env *env, t_cmd_lst **cmds)
{
	t_lst	*tokens;
	char	**strs;

	DEBUG && printf("script = \"%s\"\n", script);
	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = NULL;
	lexer(strs, &tokens);
	DEBUG && print_token_list(tokens);
	replace(tokens, env);
	DEBUG && print_token_list(tokens);
	if(here_doc(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parser(tokens, cmds);
	free_strings(strs);
	ft_lstclear2(&tokens, free_token_without_close);
	// free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}
