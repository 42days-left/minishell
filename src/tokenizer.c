/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:35:03 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/30 13:46:40 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @example $prompt : 'hello "hola world" world' -> one set. not two.
 */
int	convert_quote(char *script)
{
	char	in_quote;

	while (*script != '\0')
	{
		if (*script == '\"' || *script == '\'')
		{
			in_quote = *script;
			script++;
			while (*script != '\0' && *script != in_quote)
			{
				*script = *script * -1;
				script++;
			}
			if (*script == '\0')
				return (EXIT_FAILURE);
		}
		script++;
	}
	return (EXIT_SUCCESS);
}

int	reconvert_quote(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\"' || *str == '\'')
		{
			str++;
			while (*str != '\0' && *str < 0)
			{
				*str = *str * -1;
				str++;
			}
			if (*str == '\0')
				return (EXIT_FAILURE);
		}
		str++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @example 'echo|sleep 3' -> 'echo | sleep 3'
 * base on @ycha
 */
int	convert_symbols(char *script, char *buf)
{
	while (*script != '\0')
	{
		if (ft_strchr("()?;\\", *script))
			return (EXIT_FAILURE);
		if (ft_strchr("|<>", *script))
		{
			*buf++ = ' ';
			*buf++ = *script;
			if (*script == *(script + 1))
				*buf++ = *script++;
			*buf = ' ';
		}
		else
			*buf = *script;
		buf++;
		script++;
	}
	*buf = '\0';
	return (EXIT_SUCCESS);
}

int	tokenizer(char *script, char ***strs)
{
	int		i;
	char	buf[BUF_SIZE];

	if (convert_quote(script) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	convert_symbols(script, buf);
	*strs = ft_split(buf, ' ');
	i = 0;
	while ((*strs)[i])
	{
		reconvert_quote((*strs)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
