/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:21:56 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 17:31:55 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 없는 환경 변수를 찾으면 삭제 해야한다.
 * @example echo "[Hello asdf ][$USSR][ ][$USER]" -> Hello asdf devleo
 */

int	copy_before_dollar(char **ptr, char **buf)
{
	while (**ptr)
	{
		if (**ptr == '$')
			return (TRUE);
		if (**ptr == '\'')
		{
			*(*buf)++ = *(*ptr)++;
			while (**ptr && **ptr != '\'')
			{
				DEBUG && printf("[%c]\n", **ptr);
				*(*buf)++ = *(*ptr)++;
			}
		}
		*(*buf)++ = *(*ptr)++;
	}
	return (FALSE);
}

int	is_valid_env_char(char c)
{
	if (c && !ft_isspace(c) && (ft_isalnum(c) || c == '_' ))
		return (TRUE);
	return (FALSE);
}

char	*find_key_from_str(char *str_ptr)
{
	char	buf[BUF_SIZE];
	int		i;

	if (ft_isdigit(str_ptr[0]) || ft_isspace(str_ptr[0]) || str_ptr[0] == 0)
		return (NULL);
	buf[0] = str_ptr[0];
	i = 1;
	while (is_valid_env_char(str_ptr[i]))
	{
		buf[i] = str_ptr[i];
		i++;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}

t_env	*find_env_from_env(char *in_key, t_env *env)
{
	t_env	*curr;

	curr = env;
	if (in_key[0] == '?')
		return (new_env_node("?", ft_itoa(g_exitstat)));
	while (curr)
	{
		if (ft_strncmp(curr->key, in_key, 10000) == SAME)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
		return (NULL);
	return (curr);
}

static void	free_compound_cmd_node(t_env *tmp)
{
	if (tmp && tmp->key[0] == '?')
	{
		free(tmp->value);
		free(tmp);
	}
}

static int	is_single_dollar(char next_dollar)
{
	if (next_dollar == '\0' || next_dollar == '\"' || ft_isspace(next_dollar))
		return (TRUE);
	return (FALSE);
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
	tmp = NULL;
	while (copy_before_dollar(&str_ptr, &buf_ptr))
	{
		str_ptr++;
		if (is_single_dollar(*str_ptr))
			return (EXIT_SUCCESS);
		str_key = find_key_from_str(str_ptr);
		if (str_key == NULL)
			break ;
		tmp = find_env_from_env(str_key, env);
		if (tmp && tmp->value)
		{
			ft_memcpy(buf_ptr, tmp->value, ft_strlen(tmp->value));
			buf_ptr += (char)ft_strlen(tmp->value);
		}
		str_ptr += (char)ft_strlen(str_key);
		free(str_key);
	}
	*buf_ptr = '\0';
	free(token->word);
	free_compound_cmd_node(tmp);
	token->word = ft_strdup(buf);
	return (EXIT_SUCCESS);
}

void	remove_quote_token(t_token *token)
{
	char	buf[BUF_SIZE];
	char	*str_ptr;
	char	*buf_ptr;
	char	in_quote;

	if (token->type == PIPE)
		return ;
	str_ptr = token->word;
	buf_ptr = buf;
	in_quote = 0;
	while (*str_ptr != '\0')
	{
		if (in_quote == 0 && (*str_ptr == '\"' || *str_ptr == '\''))
		{
			in_quote = *str_ptr;
			str_ptr++;
		}
		if (*str_ptr == in_quote)
		{
			in_quote = 0;
			str_ptr++;
		}
		*buf_ptr++ = *str_ptr++;
	}
	*buf_ptr = '\0';
	free(token->word);
	token->word = ft_strdup(buf);
}

int	replace(t_lst *tokens, t_env *env)
{
	t_lst	*curr;

	curr = tokens;
	while (curr)
	{
		replace_env_token(curr->data, env);
		remove_quote_token(curr->data);
		curr = curr->next;
	}
	return (0);
}
