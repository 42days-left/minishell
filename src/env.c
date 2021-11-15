/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/12 13:55:12 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * 없는 환경 변수를 찾으면 삭제 해야한다.
 * @example echo "[Hello asdf ][$USSR][ ][$USER]" -> Hello asdf devleo
 */


int	find_dollor_addr(t_token *value)
{
	char	*str;

	str = value->arg;
	//내 생각에는 while로 char하나씩 보면서 처리해야 할것 같다.
	if (ft_strchr(str, '$'))
	{
		printf("I find $ sign!!\n");
		return (TRUE);
	}
	return (FALSE);
}

t_lst	*str_2_lst(char *str)
{
	t_lst	*lst;
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			i++;
		i++;
	}

	return (lst);
}

int	replace_env(t_lst *tokens, t_env *env)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		printf("[%d]\n", i++);
		if (find_dollor_addr(tokens->value))
		{
			/* "Hello $USSR $USER world" */
			/* ["Hello ][$USSR ][$USER][ ][world"] */
			str_2_lst(((t_token *)(tokens->value))->arg);
				/* start -> ~'$'만날 때 까지. */
				/* start -> ~'$'만날 때 까지. */
			find_lst_key();
			change_dollor();
			lst_2_str();
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
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
