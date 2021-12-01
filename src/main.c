/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/01 01:33:43 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

void	free_strings(char **strs)
{
	int i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * @param script string entered at the prompt
 */
int	parse(char *script, t_env *env, t_cmd_lst **cmds)
{
	t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = NULL;
	lexer(strs, &tokens);
	DEBUG && print_token_list(tokens);
	replace(tokens, env);
	DEBUG && print_token_list(tokens);
	parser(tokens, cmds);
	free_strings(strs);
	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;
	t_cmd_lst	*cmds;
	t_cmd_arg	*test;

	(void)argc;
	(void)argv;
	env = get_envp(envp);
	set_signal();
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		add_history(str);
		if (!str)
			ft_exit(1, NULL);
		cmds = (t_cmd_lst *)malloc(sizeof(t_cmd_arg));
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_FAILURE)
				exit_err(2, "Parse Error");
			execute(cmds, env);
		}
		free(str);
		free(cmds);
	}
	return (0);
}
