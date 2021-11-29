/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devleo <devleo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:12:15 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/28 17:29:57 by devleo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* linked list
 * ----------------
 * - lst_search
 * - lst_insert@
 * - lst_clear@
 * - lst_print@
 * - lst_new@
 * - lst_del?
 * ... 등등드읃응
 * */

t_lst	*lst_search(t_lst *head, char *target)
{
	t_lst	*curr;

	if (head == NULL)
		return (0);
	curr = head;
	while (curr != NULL)
	{
		/* string search를 해야함 */
		if (curr->data == target)
			break ;
		curr = curr->next;
	}
	return (curr);
}

t_lst	*lst_new(void *value)	//int value 아님 암튼 아님;
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (new == NULL)
	{
		printf(RED"MALLOC ERROR\n"RESET);
		exit(12); //12가 무엇인지 확인해보기
	}
	new->data = value;
	new->next = NULL;
	return (new);
}

t_lst	*lst_init()
{
	return (lst_new(NULL));
}

void	lst_insert(t_lst *before, t_lst *new)
{
	new->next = before->next;
	before->next = new;
}

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

int	lst_size(t_lst *head)
{
	int		size;
	t_lst	*curr;

	size = 0;
	curr = head;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	lst_del(t_lst *lst)
{

}

void	lst_add_front(t_lst **lst, t_lst *new)
{
	if (new == NULL)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

t_lst	*lst_last(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	if (lst == NULL)
		return (NULL);
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

/**
 * @brief lst tail 뒤에 새 노드 *new를 추가하는 함수, lst가 없으면 *new를 lst의 head로 준다.
 *
 * @param lst
 * @param new
 */
void	lst_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst == NULL || new == NULL)
	{
		printf(RED"LST_ADD_BACK ERR\n"RESET);
		return ;
	}
	if (*lst)
	{
		last = lst_last(*lst);
		new->next = last->next;
		last->next = new;
	}
	else
	{
		*lst = new;
		return ;
	}
}

void	lst_add_back_token(t_lst **lst, t_token *new)
{
	lst_add_back(lst, lst_new(new));
}

/* list -> **str function */
char	**lst_to_str(t_lst head)
{
	return (0);
}

/* list <- **str function */
t_lst	*str_to_lst()
{
	return (0);
}
