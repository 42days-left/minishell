/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:12:15 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/21 14:22:34 by yubae            ###   ########.fr       */
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

/* union으로 처리하면 더 쉬울수 있어요. 근데...? 틀렸을 수도 아닐 수도 맞을 수도.. by @jiwchoi */
/* 유니온을 공부 해야 합니다. */
union u_con
{
	char	*str;
	char	c;
};

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
	curr = head->next;
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
 * *lst tail 뒤에 새 노드 *new를 추가하는 함수
 * *lst가 없으면 *new를 lst의 head로 준다.
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
		//printf("LST ADD BACK!!\n");
		last = lst_last(*lst);
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

//왜 NULL 부터 시작해?
void	lst_add_back_token(t_lst **lst, t_token *new)
{
	lst_add_back(lst, lst_new(new));
}

//void	print_lst_nul(t_lst *head)
//{
//	t_lst	*curr;
//	t_token *t;
//	char	*tmp1;
//	char	*tmp2;
//
//	curr = head;
//	while (curr->next != NULL)
//	{
//		t = (t_tokens *)(curr->value);
//		tmp1 = t->type;
//		tmp2 = t->value;
//		printf("[%s] ", tmp1);
//		printf("[%s] ", tmp2);
//		curr = curr->next;
//	}
//		t = (t_tokens *)(curr->value);
//		tmp1 = t->type;
//		tmp2 = t->value;
//		printf("[%s] ", tmp1);
//		printf("[%s] ", tmp2);
//}
//
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
