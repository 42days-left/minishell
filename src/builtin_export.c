/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/29 20:32:30 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_key_in_env(char *key, t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{

		curr = curr->next;
	}
	return (TRUE);
}

int	is_valid_key(char *key)
{
	int	i;

	if (ft_isdigit(key[0]) || ft_isspace(key[0]))
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
	t_env	*curr;
	t_env	*tmp;
	t_env	*tmp2;
	int		i;

	if (argc == 1)
		print_export_lst(env);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (!is_valid_key(argv[i]))
				printf(RED"export : '%s' : not a valid identifier\n"RESET, argv[i]);
			else
			{
				tmp = get_env_line(argv[i]);
				printf("tmp : %s"MAGENTA"="RESET"%s\n", tmp->key, tmp->value);
				tmp2 = find_env_from_env(tmp->key, env);
				if (tmp2)
				{
					printf("tmp2 : %s"MAGENTA"="RESET"%s\n", tmp2->key, tmp2->value);
					tmp2->value = tmp->value;
					printf("AFTER tmp : %s"MAGENTA"="RESET"%s\n", tmp->key, tmp->value);
					// break ;
				}
				else
				{
					env_add_back(&env, tmp);
					// break;
				}
				printf(GREEN"export : '%s' : is valid KEY!\n"RESET, argv[i]);
			}
			i++;
		}

	}

	return(EXIT_SUCCESS);
}
