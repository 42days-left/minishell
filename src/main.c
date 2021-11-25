/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/25 17:00:44 by jisokang         ###   ########.fr       */
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

char	**get_cmd_argv(int argc, t_lst *args)
{
	t_lst	*curr;
	char	**str;
	int		i;

	curr = args;
	i = 0;
	printf("HI!");
	str = malloc(sizeof(char *) * argc);
	if (!str)
		exit_err(2, "malloc err");
	while (curr)
	{
		str[i] = ft_strdup(((t_token *)args->data)->arg);
		i++;
		curr = curr->next;
	}
	return(str);
}

t_cmd_arg	*parse_cmd_arg(t_cmd *cmd, t_env *env)
{
	t_cmd_arg	*cmd_arg;

	printf("parse_cmd_arg START\n");
	cmd_arg = malloc(sizeof(t_cmd_arg));
	if (!cmd_arg)
		exit_err(2, "malloc err");
	cmd_arg->argc = lst_size(cmd->args);
	printf("lst_size done\n");
	cmd_arg->argv = get_cmd_argv(cmd_arg->argc, cmd->args);
	printf("get_cmd_argv done\n");
	cmd_arg->env = env;
	printf("env done\n");
	cmd_arg->fd[READ] = 0;
	cmd_arg->fd[WRITE] = 0;
	return (cmd_arg);
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
	t_cmd_arg	*test;

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
			test = parse_cmd_arg(cmds->cmd, env);
			int i = 0;
			printf("test->argv : ");
			while (test->argv[i])
			{
				printf(CYAN"%s "RESET, test->argv[i]);
				i++;
			}
			printf("\n");

			//print_cmds_list(cmds);
			//builtin_function(cmds->cmd, env);
			/*!!!!!!!!!!!!!!!!!*/
			//execute(cmds, env);
			/*!!!!!!!!!!!!!!!!!*/
		}
		free(str);
	}
	return (0);
}
