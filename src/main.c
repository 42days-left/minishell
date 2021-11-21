/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/21 21:07:55 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1

/**
 * @param script string entered at the prompt
 */
int	parse(char *script, t_env *env, t_lst *cmds)
{
	t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = NULL;
	lexer(strs, &tokens);
	print_token_list(tokens);
	replace(tokens, env);
	print_token_list(tokens);
	printf("PARSER STRAT\n");
	parser(tokens, &cmds);
	printf("PARSER "GREEN"DONE"RESET"\n");
	print_cmds_list(cmds);
	//free_strings(strs)
	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}


int builtin_function(t_lst *cmds, t_env *env)
{
	char *cmd;
	t_lst *curr;
	
	curr = ((t_cmd *)(cmds->data))->args;
	cmd = ((t_token *)(cmds->data))->arg;
	printf("builtin\n");
	if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exit();
//	else if (!ft_strncmp(cmd, "env", 4))
//		ft_env(env);
	else if (!ft_strncmp(cmd, "cd", 2))
		ft_cd(cmds, env);
//	else
//		exec_fork(cmd, env);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;
	t_lst	*cmds;

	(void)argc;
	(void)argv;
	//print_envp(envp);
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		//cmds = lst_init();
		cmds = NULL;
		if (str)
		{
			printf("input\t: %s\n", str);
			parse(str, env, cmds);
			builtin_function(cmds, env);
			/*!!!!!!!!!!!!!!!!!*/
			//execute(cmds, env);
			/*!!!!!!!!!!!!!!!!!*/
		}
		else
			break ;
		add_history(str);
		free(str);
	}
	return (0);
}
