/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:07:31 by yubae             #+#    #+#             */
/*   Updated: 2021/12/23 16:00:50 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dot_path(char *path)
{
	if (path[0] == '.')
	{
		if (path[1] == '\0')
			exit_err(EXIT_SYNTAXERR, ".: filename argument required");
		else if (path[1] == '.' && path[2] == '\0')
			exit_err(EXIT_WRONGPATH, "..: command not found");
	}
}

char	*find_path_extern(char *in_path, t_env *env)
{
	int			i;
	t_env		*tmp;
	char		*new_path;
	char		**path_arr;
	struct stat	s;

	tmp = find_env_from_env("PATH", env);
	if (!tmp)
		return (NULL);
	path_arr = ft_split(tmp->value, ':');
	i = 0;
	while (path_arr[i])
	{
		tmp->value = ft_strjoin("/", in_path);
		new_path = ft_strjoin(path_arr[i], tmp->value);
		free(tmp->value);
		//free(tmp);
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *in_path, t_env *env)
{
	struct stat	s;

	DEBUG && printf("------------"GREEN"FIND NEW_PATH"RESET"----------\n");
	if (!stat(in_path, &s))
	{
		check_dot_path(in_path);
		if ((s.st_mode & S_IFMT) == S_IFDIR)
		{
			printf(YELLOW"%s: "RESET, in_path);
			exit_err(EXIT_EXCUTE, "is a directory");
		}
		return (in_path);
	}
	if (in_path[0] == '/')
	{
		printf(YELLOW"%s: "RESET, in_path);
		exit_err(EXIT_WRONGPATH, "No such file or directory");
	}
	return (find_path_extern(in_path, env));
}
