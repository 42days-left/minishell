/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 20:20:30 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1

/**
 * @param script string entered at the prompt
 */

int print_token(t_token *token)
{
	char  *c;

	if (token->type == PIPE)
		c = "PIPE";
	else
		c = "else";
	printf("type: %s, value: %s\n", c, token->arg);
	return (1);
}


int print_token_list(t_lst *tokens)
{
	t_lst *node;

	node = tokens->next;
	while(node)
	{
		print_token(node->value);
		node = node->next;
	}
	return (1);
}

int	parse(char *script)
{
	t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = lst_init();
	lexer(strs, tokens);
	
	print_token_list(tokens);
	
	//relace_env();
	//parser();
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;

	(void)argc;
	(void)argv;
	print_envp(envp);
	get_envp(envp);
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
