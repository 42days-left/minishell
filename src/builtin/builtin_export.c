/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 16:54:29 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_node_to_env_var(t_env *node, t_env *env)
{
	t_env	*tmp;

	tmp = find_env_from_env(node->key, env);
	if (tmp)
	{
		free(tmp->value);
		if (node->value)
			tmp->value = ft_strdup(node->value);
		free_env_node(node);
	}
	else
		env_add_back(&env, node);
}

int	set_export_var(int argc, char **argv, t_env *env)
{
	t_env	*argv_env;
	t_env	*tmp;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_key_value(argv[i]))
			printf(YELLOW"export : '%s' : not a valid identifier\n"\
			RESET, argv[i]);
		else
		{
			argv_env = get_env_from_str(argv[i]);
			set_node_to_env_var(argv_env, env);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	free_copyed_env(t_env *head)
{
	t_env	*curr;
	t_env	*next;

	curr = head;
	if (!curr)
		return ;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void	print_export_lst(t_env *head, int fd_out)
{
	t_env	*curr;
	t_env	*tmp;

	curr = head->next;
	while (curr)
	{
		if (ft_strncmp(curr->key, "_", 2) != SAME)
		{
			ft_putstr_fd(GRAY"declare -x "RESET, fd_out);
			ft_putstr_fd(curr->key, fd_out);
			if (curr->value)
			{
				ft_putstr_fd(MAGENTA"="RESET, fd_out);
				ft_putstr_fd("\"", fd_out);
				ft_putstr_fd(curr->value, fd_out);
				ft_putstr_fd("\"", fd_out);
			}
			ft_putstr_fd("\n", fd_out);
		}
		curr = curr->next;
	}
}

int	builtin_export(int argc, char **argv, t_env *env, int fd_out)
{
	t_env	*copy_head;

	if (argc == 1)
	{
		copy_head = sort_export_lst(env);
		print_export_lst(copy_head, fd_out);
		free_copyed_env(copy_head);
		return (EXIT_SUCCESS);
	}
	if (set_export_var(argc, argv, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
