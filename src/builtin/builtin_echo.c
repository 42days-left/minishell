/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 00:34:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/10 17:08:18 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief builtin echo with option '-n'
 *
 * @param argc
 * @param argv
 * @return int 0
 */
int	builtin_echo(int argc, char **argv, int fd)
{
	int	opt;
	int	i;

	i = 1;
	if (argc == 1)
	{
		ft_putstr_fd("\n", fd);
		return (EXIT_SUCCESS);
	}
	opt = FALSE;
	if (!ft_strncmp("-n", argv[1], 3))
	{
		opt = TRUE;
		i++;
	}
	while (i < argc - 1)
	{
		ft_putstr_fd(argv[i++], fd);
		ft_putstr_fd(" ", fd);
	}
	if (argv[i] != NULL)
		ft_putstr_fd(argv[i++], fd);
	if (opt == FALSE)
		ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}
