/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 14:26:37 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_envp(t_env *env)
{
	t_env	*curr;
	char	**envp;
	char	*tmp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (env_count(env) + 1));
	if (!envp)
		return (NULL);
	curr = env;
	i = 0;
	while (curr != NULL)
	{
		tmp = ft_strjoin("=", curr->value);
		envp[i] = ft_strjoin(curr->key, tmp);
		free(tmp);
		curr = curr->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}

void	free_envp(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

t_env	*get_env_from_str(char *str)
{
	t_env	*node;
	char	*curr;

	curr = str;
	while (*curr != '\0')
	{
		if (*curr == '=')
		{
			*curr = '\0';
			node = new_env_node(ft_strdup(str), ft_strdup(curr + 1));
			*curr = '=';
			return (node);
		}
		curr++;
	}
	if (curr != str)
		return (new_env_node(ft_strdup(str), NULL));
	return (0);
}

t_env	*get_envp(char **envp)
{
	int		i;
	t_env	*env_lst;

	env_lst = NULL;
	i = 0;
	while (envp[i])
		env_add_back(&env_lst, get_env_from_str(envp[i++]));
	return (env_lst);
}
