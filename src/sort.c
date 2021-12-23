/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 22:39:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/22 14:49:07 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_string(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	sort_alpha(t_env *begin_list)
{
	t_env	*list;
	t_env	*idx;

	list = begin_list->next;
	while (list)
	{
		idx = list->next;
		while (idx)
		{
			if (ft_strncmp(list->key, idx->key, ft_strlen(list->key) + 1) > 0)
			{
				swap_string(&list->key, &idx->key);
				swap_string(&list->value, &idx->value);
			}
			idx = idx->next;
		}
		list = list->next;
	}
}

t_env	*sort_export_lst(t_env *env)
{
	t_env	*copy_head;
	t_env	*curr;

	copy_head = NULL;
	env_add_back(&copy_head, new_env_node(NULL, NULL));
	curr = env->next;
	while (curr)
	{
		env_add_back(&copy_head, new_env_node(curr->key, curr->value));
		curr = curr->next;
	}
	sort_alpha(copy_head);
	return (copy_head);
}
