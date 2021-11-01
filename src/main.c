/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 12:14:08 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1
#define		BUF_SIZE	100000

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
	if (*str == '\"' || *str == '\'')
	{
		str++;
		while (*str != '\0' && *str < 0)
		{
			*str = *str * -1;
			str++;
		}
	}
	return (0);
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
			printf("FOUND SYMBOLS!\n");
			/* 1. Add space Here*/
			/* Buffer? */
			/* 2. n-split -> join */
			*buf++ = ' ';
			*buf++ = *script;
			if (*script == *(script + 1))
				*buf = *script++;
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
/*
int	split_symbols(char *str)
{
	int	i;

	while (*str != '\0')
	{
		if (ft_strchr("|<>", *str))
		{
		}
		str++;
	}
	str = ft_split();

	if (*str == '\"' || *str == '\'')
	{
		str++;
		while (*str != '\0' && *str < 0)
		{
			*str = *str * -1;
			str++;
		}
	}
}*/

int	tokenizer(char *script, char ***strs)
{
	int		i;
	char	buf[BUF_SIZE];

	if (convert_quote(script) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	convert_symbols(script, buf);
	//count_symbols(script);
	//스크립트 심볼에 ' '을 삽입하기 위해 버퍼가 필요한 시점
	*strs = ft_split(buf, ' ');
	i = 0;
	while ((*strs)[i])
	{
		reconvert_quote((*strs)[i]);
		printf("[%s]\n", (*strs)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @param script string entered at the prompt
 */
int	parse(char *script)
{
	//t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(!tokenizer(script, &strs))
		return (EXIT_FAILURE);
	//lexer(script, tokens);
	//relace_env();
	//parser();
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
	t_lst	*last;

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

}

char	*get_env_key_value(char *str)
{
	char	return_box[2];
	char	*curr;

	curr = str;
	while (*curr != '\0')
	{
		if (*curr == '=')
		{
			*curr = '\0';
			return_box[KEY] = ft_strdup(*str);
			return_box[VALUE] = ft_strdup(*(curr + 1));
			return (return_box);
		}
		curr++;
	}
}

int	get_envp(char **envp)
{
	int		i;

	while (*envp != NULL)
	{
		i = 0;
		while (**envp != '=')
			i++;

		envp++;
	}

}

int	main(int argc, char **argv, char **envp)
{
	char *str;

	(void)argc;
	(void)argv;
	print_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		if (str)
		{
			printf("input\t: %s\n", str);
			parse(str);
		}
		else
			break ;
		add_history(str);
		free(str);
	}
	return(0);
}
