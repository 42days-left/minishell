/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 13:26:59 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_envp_lst(t_env *head, int fd_out)
{
	t_env	*curr;

	curr = head;
	while (curr->next != NULL)
	{
		ft_putstr_fd(curr->key, fd_out);
		ft_putstr_fd(MAGENTA"="RESET, fd_out);
		ft_putstr_fd(curr->value, fd_out);
		ft_putstr_fd("\n", fd_out);
		curr = curr->next;
	}
	ft_putstr_fd(curr->key, fd_out);
	ft_putstr_fd(MAGENTA"="RESET, fd_out);
	ft_putstr_fd(curr->value, fd_out);
	ft_putstr_fd("\n", fd_out);
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

// char	*search_env_lst(t_env **lst, char *key)
// {
// 	return (0);
// }

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

t_env	*get_env_from_str2(char *str)
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
