/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:21:56 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 16:55:53 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	curr = env->next;
	if (in_key[0] == '?')
		return (new_env_node("?", ft_itoa(g_exitstat)));
	while (curr)
	{
		if (ft_strncmp(curr->key, in_key, ft_strlen(in_key) + 1) == SAME)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
		return (NULL);
	return (curr);
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
