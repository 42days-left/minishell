/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:11:54 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 12:55:34 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key_value(char *key)
{
	int	i;

	if (key[0] == '\0' || ft_isdigit(key[0]) || !is_valid_env_char(key[0]))
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

int	set_export_var(int argc, char **argv, t_env *env)
{
	t_env	*argv_env;
	t_env	*tmp;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_key_value(argv[i]))
			printf(YELLOW"export : '%s' : not a valid identifier\n"RESET, argv[i]);
		else
		{
			argv_env = get_env_from_str(argv[i]);
			tmp = find_env_from_env(argv_env->key, env);
			if (tmp)
				tmp->value = argv_env->value;
			else
				env_add_back(&env, argv_env);
		}
		i++;
	}
	// free(argv_env->key);
	// free(argv_env->value);
	// free(argv_env);
	// malloc: *** error for object 0x333231: pointer being freed was not allocated
	// malloc: *** set a breakpoint in malloc_error_break to debug
	return (EXIT_SUCCESS);
}

//env lst를 하나하나 버블 소팅을 할꺼야.
//이 리스트를 직접 소팅하는게 아니라 새로 복사해서 할꺼야
//그리고 그 리스트는 쓰고 free할 거임 GOOD
void	sort_env_key_lst(t_env *env)
{
	t_env	*curr;
	int		len;

	curr = env;
	len = env_lst_size(curr);
	while (curr)
	{
		// env_add_back(z);
		curr = curr->next;
	}
}

void	print_export_lst(t_env *env, int fd_out)
{
	t_env	*curr;

	curr = env;
	while (curr)
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
		curr = curr->next;
	}
}

int	builtin_export(int argc, char **argv, t_env *env, int fd_out)
{
	if (argc == 1)
	{
		env_sort(env);
		print_export_lst(env, fd_out);
		return (EXIT_SUCCESS);
	}
	if (set_export_var(argc, argv, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
