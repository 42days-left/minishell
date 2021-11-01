/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 15:39:12 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1

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
