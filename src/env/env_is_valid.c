/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:54:08 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 16:55:33 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_char(char c)
{
	if (c && !ft_isspace(c) && (ft_isalnum(c) || c == '_' ))
		return (TRUE);
	return (FALSE);
}

int	is_valid_key(char *key)
{
	int	i;

	if (key[0] == '\0' || ft_isdigit(key[0]) || !is_valid_env_char(key[0]))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (key[i] == '=')
			return (FALSE);
		else if (!is_valid_env_char(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_valid_key_value(char *key)
{
	int	i;

	if (key[0] == '\0' || ft_isdigit(key[0]) || !is_valid_env_char(key[0]))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		else if (!is_valid_env_char(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
