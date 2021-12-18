/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:53:17 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 16:28:22 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_arg(t_cmd_arg *ca)
{
	DEBUG && printf("free_cmd_arg\tSTART\n");
	free_strings(ca->argv);
	fd_close(ca->fd_in);
	fd_close(ca->fd_out);
	// free(ca->env);
	free(ca);
	DEBUG && printf("free_cmd_arg\tDONE\n");
}

void	free_tokens(t_lst *tokens)
{
	t_lst	*curr;

	curr = tokens;
	while (curr)
	{
		// free(((t_token *)curr->data)->type);
		free(((t_token *)curr->data)->word);
		curr = curr->next;
	}
	lst_clear(tokens);
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	// free_tokens(&cmd->tokens);
	ft_lstclear2(&cmd->tokens, free_token_without_close);
	ft_lstclear2(&cmd->rd, free_token_without_close);
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

void	free_strings(char **strs)
{
	int i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
