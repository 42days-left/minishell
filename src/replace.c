/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:21:56 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/17 15:37:02 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			printf("HELLO!\n");
			*(*buf)++ = *(*ptr)++;
			while (**ptr && **ptr != '\'')
			{
				printf("[%c]\n", **ptr);
				*(*buf)++ = *(*ptr)++;
			}
		}
		*(*buf)++ = *(*ptr)++;
	}
	return (FALSE);
}

int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (TRUE);
	return (FALSE);
}

static int	is_alpha_env(char c)
{
	if (c && !ft_isspace(c) && (ft_isalpha(c) || c == '_'))
		return (TRUE);
	return (FALSE);
}

char	*find_key_from_str(char *str_ptr)
{
	char	buf[BUF_SIZE];
	int		i;

	if (ft_isdigit(str_ptr[0]) || ft_isspace(str_ptr[0]))
		return (NULL);
	buf[0] = str_ptr[0];
	i = 1;
	while (is_alpha_env(str_ptr[i]))
	{
		buf[i] = str_ptr[i];
		i++;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}

char	*find_value_from_env(char *in_key, t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		printf("["YELLOW"%s"RESET"]\n", curr->key);
		if (ft_strncmp(curr->key, in_key + 1, 10000) == SAME)	//in_key + 1 = '$'다음 문자들
			break;
		curr = curr->next;
	}
	if (curr == NULL)
		return (NULL);
	return (curr->value);
}

int	replace_env_token(t_token *token, t_env *env)
{
	char	buf[BUF_SIZE];
	char	*buf_ptr;
	char	*str_ptr;
	char	*str_key;
	char	*env_value;

	str_ptr = token->arg;
	buf_ptr = buf;
	while (copy_before_dollar(&str_ptr, &buf_ptr))
	{
		str_key = find_key_from_str(str_ptr);
		printf("str_key = ["BLUE"%s"RESET"]\n", str_key);
		env_value = find_value_from_env(str_key, env);
		if (env_value)
		{
			ft_memcpy(buf_ptr, env_value, ft_strlen(env_value));
			buf_ptr += (char)ft_strlen(env_value);
		}
		str_ptr += (char)ft_strlen(str_key);
	}
	*buf_ptr = '\0';
	free(token->arg);
	token->arg = ft_strdup(buf);
	return (EXIT_SUCCESS);
}

void	remove_quote_token(t_token *token)
{
	char	buf[BUF_SIZE];
	char	*str_ptr;
	char	*buf_ptr;

	str_ptr = token->arg;
	buf_ptr = buf;
	while (*str_ptr != '\0')
	{
		printf("["RED"%c"RESET"]\n", *str_ptr);
		while (*str_ptr == '\"' || *str_ptr == '\'')
			str_ptr++;
		*buf_ptr++ = *str_ptr++;
	}
	*buf_ptr = '\0';
	printf("buf : [%s]\n", buf);
	free(token->arg);
	token->arg = ft_strdup(buf);
}

int	replace(t_lst *tokens, t_env *env)
{
	t_lst	*curr;

	curr = tokens;
	printf("REPLACE START\n");
	while (curr)
	{
		replace_env_token(curr->value, env);
		remove_quote_token(curr->value);
		curr= curr->next;
	}
	printf("REPLACE "GREEN"DONE\n"RESET);
	return (0);
}
