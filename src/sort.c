/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 22:39:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/02 00:27:19 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	env_sort(t_env *head)
{
	int		size;
	t_env	*curr;

	curr = head;
	size = env_lst_size(curr);
	printf("size is = [%d]\n", size);
}
