/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:24 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/22 15:01:38 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_err(int num, char *msg)
{
	printf(RED "Error\n" RESET);
	printf("["YELLOW "%d"RESET"] "YELLOW"%s\n"RESET, num, msg);
	exit (num);
}
