/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:12:15 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 17:18:50 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_lst	*lst_init(void)
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

void	free_token_without_close(void *void_token)
{
	t_token	*token;

	token = (t_token *)void_token;
	if (token->word)
		free(token->word);
	free(token);
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

void	lst_del(t_lst *head, int key)
{
	// Store head node
	t_lst	*temp;
	t_lst	*prev;

	temp = head;
	// If head node itself holds the key to be deleted
	if (temp != NULL && *(int *)(temp->data) == key)
	{
		*head = *temp->next; // Changed head
		free(temp); // free old head
		return ;
	}
	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && *(int *)(temp->data) != key)
	{
		prev = temp;
		temp = temp->next;
	}
	// If key was not present in linked list
	if (temp == NULL)
		return ;
	// Unlink the node from linked list
	prev->next = temp->next;
	free(temp); // Free memory
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
// char	**lst_to_str(t_lst head)
// {
// 	return (0);
// }

/* list <- **str function */
// t_lst	*str_to_lst()
// {
// 	return (0);
// }
