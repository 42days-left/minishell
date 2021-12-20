/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:46:26 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 20:01:49 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_envp(char **envp)
{
	printf(BLUE"----------[PRINT ENVP START]----------\n"RESET);
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	printf(RED"----------[PRINT ENVP END]----------\n"RESET);
	return (0);
}

static void	print_envp_line(t_env *head, int fd_out)
{
	t_env	*curr;

	curr = head;
	if (curr->value != NULL)
	{
		ft_putstr_fd(curr->key, fd_out);
		ft_putstr_fd(MAGENTA"="RESET, fd_out);
		ft_putstr_fd(curr->value, fd_out);
		ft_putstr_fd("\n", fd_out);
	}
}

void	print_envp_lst(t_env *head, int fd_out)
{
	t_env	*curr;

	curr = head;
	while (curr->next != NULL)
	{
		print_envp_line(curr, fd_out);
		curr = curr->next;
	}
	print_envp_line(curr, fd_out);
}
