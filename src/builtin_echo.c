/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 00:34:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/01 15:02:05 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief builtin echo with option '-n'
 *
 * @param argc
 * @param argv
 * @return int 0
 */
int	builtin_echo(int argc, char **argv)
{
	int	opt;
	int	i;

	opt = FALSE;
	i = 1;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp("-n", argv[1], 3))
	{
		opt = TRUE;
		i++;
	}
	while (i < argc - 1)
		printf("%s ", argv[i++]);
	if (argv[i] != NULL)
		printf("%s", argv[i]);
	if (opt == FALSE)
		printf("\n");
	return (0);
}
