/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/25 15:21:40 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_lst	*cmd_lst_new(t_cmd *cmd)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (new == NULL)
	{
		printf(RED"MALLOC ERROR\n"RESET);
		exit(12); //12가 무엇인지 확인해보기
	}
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

	if (lst == NULL || new == NULL)
	{
		printf(RED"LST_ADD_BACK ERR\n"RESET);
		return ;
	}
	if (*lst)
	{
		//printf("LST ADD BACK!!\n");
		last = cmd_lst_last(*lst);
		new->next = last->next;
		last->next = new;
	}
	else
	{
		//printf("LST NEW!!\n");
		*lst = new;
		return ;
	}
}