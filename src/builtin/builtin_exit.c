/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:40:19 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 15:19:00 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief builtin_exit with no options
 *
 * @param argc
 * @param argv
 * @param fd_out
 * @return int
 */

int	builtin_exit(int argc, char **argv)
{
	int	stat;

	printf("exit\n");
	stat = 0;
	if (argc == 1)
		stat = 0;
	else if (!ft_isnum_str(argv[1]))
	{
		stat = 255;
		printf("exit: %s: numeric argument required\n", argv[1]);
	}
	else if (argc > 2)
	{
		printf("exit: to many arguments\n");
		return (1);
	}
	else
		stat = ft_atoi(argv[1]);
	exit(stat);
}
