/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 00:34:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/01 00:54:58 by jisokang         ###   ########.fr       */
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
	int	flag;
	int	i;

	flag = FALSE;
	i = 1;
	if (ft_strncmp("-n", argv[1], 2) == SAME)
	{
		flag = TRUE;
		i++;
	}
	while (i < argc - 1)
		printf("%s ", argv[i++]);
	printf("%s", argv[i]);
	if (flag == FALSE)
		printf("\n");
	return (0);
}
