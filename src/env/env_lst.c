/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:48:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 22:32:08 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit_err(EXIT_FAILURE, "Malloc Error");
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
	t_env	*curr;
	t_env	*prev;

	curr = head;
	if (curr != NULL && !ft_strncmp(curr->key, key, ft_strlen(key) + 1))
	{
		*head = *curr->next;
		// free(curr);
		return ;
	}
	while (curr != NULL && ft_strncmp(curr->key, key, ft_strlen(key) + 1))
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return ;
	prev->next = curr->next;
	free(curr->value);
	free(curr->key);
	free(curr);
}
