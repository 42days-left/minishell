/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/30 02:41:50 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_key(char *key)
{
	int	i;
	if (key[0] == '\0' || ft_isdigit(key[0]) || ft_isspace(key[0]))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		else if (!is_valid_env_char(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	set_export_var(int argc, char **argv, t_env *env)
{
	t_env	*curr;
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_key(argv[i]))
			printf(RED"export : '%s' : not a valid identifier\n"RESET, argv[i]);
		else
		{
			tmp = get_env_line(argv[i]);
			tmp2 = find_env_from_env(tmp->key, env);
			if (tmp2)
				tmp2->value = tmp->value;
			else
				env_add_back(&env, tmp);
			printf(GREEN"export : '%s' : is valid KEY!\n"RESET, argv[i]);
		}
		i++;
	}
}

int	print_export_lst(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		printf("declare -x %s", curr->key);
		if (curr->value)
			printf("=\"%s\"", curr->value);
		printf("\n");
		curr = curr->next;
	}
	return (TRUE);
}

int	ft_export(int argc, char **argv, t_env *env)
{
	if (argc == 1)
		print_export_lst(env);
	else
		set_export_var(argc, argv, env);
	return(EXIT_SUCCESS);
}
