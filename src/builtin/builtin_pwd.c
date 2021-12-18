/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:33:31 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 22:38:58 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd_out)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
		return (EXIT_SYNTAXERR);
	ft_putstr_fd(pwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(pwd);
	return (EXIT_SUCCESS);
}
