/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:37:20 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 15:54:19 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_cd_tilde(char **argv, t_env *tmp)
{
	char	*path;

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
	return (path);
}

int	builtin_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	t_env	*tmp;

	tmp = find_env_from_env("HOME", env);
	if (argc == 1 && tmp)
		path = tmp->value;
	else if (argc == 1 && tmp == NULL)
	{
		printf("cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	else if (argc == 2)
		path = builtin_cd_tilde(argv, tmp);
	if (chdir(path) == ERROR)
	{
		printf("cd: %s: no such file or directory\n", argv[1]);
		chdir(".");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
