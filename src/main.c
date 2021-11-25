/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/25 15:33:11 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1

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
	print_token_list(tokens);
	replace(tokens, env);
	print_token_list(tokens);
	printf("PARSER STRAT\n");
	parser(tokens, cmds);
	printf("PARSER "GREEN"DONE"RESET"\n");
	print_cmds_list(*cmds);
	//free_strings(strs)
	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}


int builtin_function(t_cmd *cmd, t_env *env)
{
	char *cmd_str;

	cmd_str = ((t_token *)cmd->args->data)->arg;
	printf("%s\n", cmd_str);
	if (!ft_strncmp(cmd_str, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd_str, "exit", 4))
		ft_exit(cmd_str);
	else if (!ft_strncmp(cmd_str, "env", 3))
		ft_env(env);
	else if (!ft_strncmp(cmd_str, "export", 6))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd_str, "cd", 2))
		ft_cd(cmd, env);
	else
		exec_fork(cmd_str, env);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;
	//t_lst	*cmds;
	t_cmd_lst	*cmds;

	(void)argc;
	(void)argv;
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		add_history(str);
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_FAILURE)
				exit_err(2, "Parse Error");
			//builtin_function(cmds->cmd, env);
			//print_cmds_list(cmds);
			/*!!!!!!!!!!!!!!!!!*/
			//execute(cmds, env);
			/*!!!!!!!!!!!!!!!!!*/
		}
		free(str);
	}
	return (0);
}
