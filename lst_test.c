/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:49:09 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/07 22:49:47 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv)
{
	t_lst	*tokens;

	tokens = NULL;
	printf("LST_ADD_START\n");
	lst_add_back(&tokens, lst_new((void *)1));
	lst_add_back(&tokens, lst_new((void *)2));
	lst_add_back(&tokens, lst_new((void *)3));
	printf("LST_ADD_END\n");

	while (tokens)
	{
		printf("tokens [%d]\n", *(int *)(&(tokens->value)));
		tokens = tokens->next;
	}

	if (tokens->value == (void *)'a')
	{
		printf("tokens 0 - ✅\n");
	}
	if (tokens->next->value == (void *)'b')
	{
		printf("tokens 1 - ✅\n");
	}
	if (tokens->next->next->value == (void *)'c')
	{
		printf("tokens 2 - ✅\n");
	}

}
