/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:37:20 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 16:38:45 by yubae            ###   ########.fr       */
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
			path = ft_strdup(getenv("HOME"));
		else
			path = tmp->value;
	}
	return (path);
}

int	builtin_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	t_env	*tmp;
	char	*pwd;
	char	*argv_pwd[3];

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
		printf(YELLOW"cd: %s: no such file or directory\n"RESET, argv[1]);
		chdir(".");
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin("PWD=", getcwd(NULL, PATH_MAX));
	argv_pwd[0] = 0;
	argv_pwd[1] = pwd;
	argv_pwd[2] = 0;
	set_export_var(2, argv_pwd, env);
	return (EXIT_SUCCESS);
}
