/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 16:22:38 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*cmd_lst_new(t_cmd *cmd)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (new == NULL)
		exit_err(EXIT_FAILURE, "Malloc Error");
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

void	cmd_lst_clear(t_cmd_lst *head)
{
	t_cmd_lst	*curr;
	t_cmd_lst	*next;

	curr = head;
	if (!curr)
		return ;
	while (1)
	{
		next = curr->next;
		free(curr);
		curr = next;
		if (curr == head)
			return ;
	}
}

int	cmd_lst_size(t_cmd_lst *head)
{
	int			size;
	t_cmd_lst	*curr;

	size = 0;
	curr = head;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

t_cmd_lst	*cmd_lst_last(t_cmd_lst *lst)
{
	t_cmd_lst	*curr;

	curr = lst;
	if (lst == NULL)
		return (NULL);
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

void	cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*last;

	if (*lst)
	{
		last = cmd_lst_last(*lst);
		new->next = last->next;
		last->next = new;
	}
	else
	{
		*lst = new;
		return ;
	}
}
