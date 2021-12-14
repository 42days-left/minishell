/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:02:58 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 17:00:13 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	if (key[0] == '\0' || ft_isdigit(key[0]) || ft_isspace(key[0]))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (key[i] == '=')
			return (FALSE);
		else if (!is_valid_env_char(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	remove_env_var(int argc, char **argv, t_env *env)
{
	t_env	*argv_env;
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_key(argv[i]))
			printf(YELLOW"unset : '%s' : not a valid identifier\n"RESET, argv[i]);
		else
		{
			argv_env = get_env_from_str(argv[i]);
			env_lst_del(env, argv_env->key);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(int argc, char **argv, t_env *env)
{
	if (argc == 1)
		return (1);
	if (remove_env_var(argc, argv, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
