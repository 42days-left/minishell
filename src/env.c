/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/16 16:01:09 by jisokang         ###   ########.fr       */
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
		printf("[%c]\n", **ptr);
		if (**ptr == '$')
			return (TRUE);
		*(*buf)++ = *(*ptr)++;
		if (**ptr == '\'')
		{
			*(*buf)++ = *(*ptr)++;
			while (**ptr && **ptr != '\'')
				*(*buf)++ = *(*ptr)++;
		}
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
	char	buf[10000];
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

	printf(YELLOW"find_value_from_env in\n"RESET);
	printf(YELLOW"in_key = [%s]\n"RESET, in_key);
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
	printf("[%s]\n", curr->value);
	return (curr->value);
}

int	replace_env_token(t_token *token, t_env *env)
{
	char	buf[10000];
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
	printf("@@@@ [%s]\n", buf);
	free(token->arg);
	token->arg = ft_strdup(buf);
	return (EXIT_SUCCESS);
}

int	replace(t_lst *tokens, t_env *env)
{
	t_lst	*curr;

	curr = tokens;
	printf("REPLACE START\n");
	while (curr)
	{
		replace_env_token(curr->value, env);
		curr= curr->next;
	}
	return (0);
}

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

void	print_envp_lst(t_env *head)
{
	t_env	*curr;
	int		i;

	curr = head;
	i = 0;
	printf(GREEN"=== ENV PRINT START ===\n"RESET);
	while (curr->next != NULL)
	{
		printf("#%d\t- [%s]"MAGENTA"="RESET"[%s]\n", i, curr->key, curr->value);
		curr = curr->next;
		i++;
	}
	printf("#%d\t- [%s]"MAGENTA"="RESET"[%s]\n", i, curr->key, curr->value);
	printf("=== ENV PRINT "GREEN"DONE"RESET" ===\n");
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		exit(1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*env_lst_last(t_env *lst)
{
	t_env	*curr;

	curr = lst;
	if (lst == NULL)
		return (NULL);
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = env_lst_last(*lst);
	new->next = last->next;
	last->next = new;
}

char	*search_env_lst(t_env **lst, char *key)
{
	return (0);
}

t_env	*get_env_line(char *str)
{
	char	*curr;

	curr = str;
	while (*curr != '\0')
	{
		if (*curr == '=')
		{
			*curr = '\0';
			return (new_env_node(ft_strdup(str), ft_strdup(curr + 1)));
		}
		curr++;
	}
	return (0);
}

t_env	*get_envp(char **envp)
{
	int		i;
	char	**box;
	t_env	*env_lst;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		env_add_back(&env_lst, get_env_line(envp[i]));
		i++;
	}
	print_envp_lst(env_lst);
	return (env_lst);
}
