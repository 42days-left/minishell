/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:33:40 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 15:49:02 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_token(void *void_token)
{
	t_token	*token;

	token = (t_token *)void_token;
	if (token->word)
		free(token->word);
	free(token);
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	ft_lstclear2(&cmd->tokens, free_one_token);
	ft_lstclear2(&cmd->rd, free_one_token);
	free(cmd);
}

void	free_cmds(t_cmd_lst **lst)
{
	t_cmd_lst	*curr;
	t_cmd_lst	*next_lst;

	curr = *lst;
	while (curr != NULL)
	{
		next_lst = curr->next;
		free_cmd(curr);
		curr = next_lst;
	}
	*lst = NULL;
}
