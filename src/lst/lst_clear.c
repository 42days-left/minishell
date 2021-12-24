/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:34:39 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 15:48:15 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear(t_lst *head)
{
	t_lst	*curr;
	t_lst	*next;

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

void	ft_lstdelone2(t_lst *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->data);
	free(lst);
}

void	ft_lstclear2(t_lst **lst, void (*del)(void *))
{
	t_lst	*curr;
	t_lst	*next_lst;

	curr = *lst;
	while (curr != NULL)
	{
		next_lst = curr->next;
		ft_lstdelone2(curr, del);
		curr = next_lst;
	}
	*lst = NULL;
}

void	lst_del(t_lst *head, int key)
{
	t_lst	*temp;
	t_lst	*prev;

	temp = head;
	if (temp != NULL && *(int *)(temp->data) == key)
	{
		*head = *temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && *(int *)(temp->data) != key)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}
