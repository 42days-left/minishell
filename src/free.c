/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:53:17 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 15:47:38 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_arg(t_cmd_arg *ca)
{
	free_strings(ca->argv);
	fd_close(ca->fd_in);
	fd_close(ca->fd_out);
	free(ca);
}

void	free_tokens(t_lst *tokens)
{
	t_lst	*curr;

	curr = tokens;
	while (curr)
	{
		free(((t_token *)curr->data)->word);
		curr = curr->next;
	}
	lst_clear(tokens);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	if (node->key)
		free(node->key);
	free(node);
}

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
