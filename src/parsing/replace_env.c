/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:47:56 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 16:49:58 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_before_dollar(char **ptr, char **buf)
{
	while (**ptr)
	{
		if (**ptr == '$')
			return (TRUE);
		if (**ptr == '\'')
		{
			*(*buf)++ = *(*ptr)++;
			while (**ptr && **ptr != '\'')
				*(*buf)++ = *(*ptr)++;
		}
		*(*buf)++ = *(*ptr)++;
	}
	return (FALSE);
}

static int	is_single_dollar(char next_dollar)
{
	if (next_dollar == '\0' || next_dollar == '\"' || ft_isspace(next_dollar))
		return (TRUE);
	return (FALSE);
}

static void	free_compound_cmd_node(t_env *tmp)
{
	if (tmp && tmp->key[0] == '?')
	{
		free(tmp->value);
		free(tmp);
	}
}

static void
	_replace_token(char *str_key, char **str_ptr, char **buf_ptr, t_env *env)
{
	t_env	*tmp;

	tmp = find_env_from_env(str_key, env);
	if (tmp && tmp->value)
	{
		ft_memcpy(*buf_ptr, tmp->value, ft_strlen(tmp->value));
		*buf_ptr += (char)ft_strlen(tmp->value);
	}
	*str_ptr += (char)ft_strlen(str_key);
	free_compound_cmd_node(tmp);
}

int	replace_env_token(t_token *token, t_env *env)
{
	char	buf[BUF_SIZE];
	char	*buf_ptr;
	char	*str_ptr;
	char	*str_key;
	t_env	*tmp;

	if (token->type == PIPE)
		return (EXIT_SUCCESS);
	str_ptr = token->word;
	buf_ptr = buf;
	while (copy_before_dollar(&str_ptr, &buf_ptr))
	{
		str_ptr++;
		if (is_single_dollar(*str_ptr))
			return (EXIT_SUCCESS);
		str_key = find_key_from_str(str_ptr);
		if (str_key == NULL)
			break ;
		_replace_token(str_key, &str_ptr, &buf_ptr, env);
		free(str_key);
	}
	*buf_ptr = '\0';
	free(token->word);
	token->word = ft_strdup(buf);
	return (EXIT_SUCCESS);
}
