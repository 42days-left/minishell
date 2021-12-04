/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:37:20 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/05 00:18:59 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	char	*home;
	t_env	*tmp;

	tmp = find_env_from_env("HOME", env);
	if (argc ==	1 && tmp)
		path = tmp->value;
	else if (argc == 1 && tmp == NULL)
	{
		printf("cd: HOME not set\n");
		return (2);
	}
	else if (argc == 2)
	{
		path = argv[1];
		if (path[0] == '~' && path[1] == 0)
		{
			if (tmp == NULL)
			{
				path = ft_strdup(getenv("HOME"));
				printf("path = [%s]\n", path);
			}
			else
				path = tmp->value;
		}
	}
	if (chdir(path) == ERROR)
	{
		printf("cd: string not in pwd: %s\n", argv[1]);
		chdir(".");
		return (2);
	}
	return (EXIT_SUCCESS);
}
