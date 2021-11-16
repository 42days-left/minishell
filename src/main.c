/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/15 20:17:59 by yubae            ###   ########.fr       */
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


int builtin_function(char *str, char **envp)
{
	char *argv[2];
	
	argv[0] = str;
	argv[1] = 0;
	if (!ft_strncmp(str, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(str, "exit", 4))
		ft_exit(str);
	else
		exec_fork(str, envp);
		//execve(getcwd(0, 1024), argv, envp);
		//exec_fork(str, envp);
	return (1);
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
		str = readline("minihell🐚: ");
		if (str)
			builtin_function(str, envp);
		printf("readline: %s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
//		if (str)
//		{
//			printf("input\t: %s\n", str);
//			parse(str);
//		}
//	}
//	else
//		break ;
//		add_history(str);
//		free(str);
//	}
//	return(0);
//}
//int	main(int argc, char **argv, char **envp)
//{
//	char *str;
//
//	(void)argc;
//	(void)argv;
//	print_envp(envp);
//	get_envp(envp);
//	while(TRUE)
//	{
//		str = readline(MAGENTA"minihell🐚"RESET": ");
//		exit_function(str);
//		if (str)
//		{
//			printf("input\t: %s\n", str);
//			parse(str);
//		}
//		else
//			break ;
//		add_history(str);
//		free(str);
//	}
//	return(0);
//}
