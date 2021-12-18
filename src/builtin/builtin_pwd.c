/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:33:31 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 15:20:21 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd_out)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
		return (2);
	ft_putstr_fd(pwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(pwd);
	return (EXIT_SUCCESS);
}
