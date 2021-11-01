/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 15:50:19 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_envp(char **envp)
{
	printf(BLUE"----------[PRINT ENVP START]----------\n"RESET);
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	printf(RED"----------[PRINT ENVP END]----------\n"RESET);
	return (0);
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
	t_lst	*last;

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

char	*search_env_lst(t_env **lst, char *key)
{

}

char	*get_env_key_value(char *str)
{
	char	return_box[2];
	char	*curr;

	curr = str;
	while (*curr != '\0')
	{
		if (*curr == '=')
		{
			*curr = '\0';
			return_box[KEY] = ft_strdup(*str);
			return_box[VALUE] = ft_strdup(*(curr + 1));
			return (return_box);
		}
		curr++;
	}
}

int	get_envp(char **envp)
{
	int		i;

	while (*envp != NULL)
	{
		i = 0;
		while (**envp != '=')
			i++;

		envp++;
	}

}
