/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:48:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 15:02:04 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_size(t_env *head)
{
	int		size;
	t_env	*curr;

	size = 0;
	curr = head;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

int	env_count(t_env *env)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = env;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		exit(1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*env_lst_last(t_env *lst)
{
	t_env	*curr;

	curr = lst;
	if (lst == NULL)
		return (NULL);
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = env_lst_last(*lst);
	new->next = last->next;
	last->next = new;
}

void	env_lst_del(t_env *head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = head;
	if (temp != NULL && !ft_strncmp(temp->key, key, ft_strlen(key)))
	{
		*head = *temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->key, key, ft_strlen(key)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}
