/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 15:40:03 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 15:42:23 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*lst_new(void *value)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (new == NULL)
		exit_err(EXIT_FAILURE, "Malloc Error");
	new->data = value;
	new->next = NULL;
	return (new);
}

t_lst	*lst_init(void)
{
	return (lst_new(NULL));
}
