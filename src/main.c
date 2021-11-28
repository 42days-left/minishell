/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devleo <devleo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/28 16:45:36 by devleo           ###   ########.fr       */
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

	int i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);

	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}

char	**get_cmd_argv(t_lst *tokens)
{
	char	**str;
	int		i;
	t_lst	*curr;

	i = 0;
	curr = tokens;
	str = (char **)malloc(sizeof(char *) * (lst_size(curr) + 1));
	if (!str)
		exit_err(2, "malloc err");
	while (curr)
	{
		str[i] = ft_strdup(((t_token *)curr->data)->word);
		curr = curr->next;
		i++;
	}
	str[i] = 0;
	return(str);
}

t_cmd_arg	*parse_cmd_arg(t_cmd *cmd, t_env *env)
{
	t_cmd		*curr;
	t_cmd_arg	*cmd_arg;
	t_token		*token;

	cmd_arg = (t_cmd_arg *)malloc(sizeof(t_cmd_arg) * 10);
	if (!cmd_arg)
		exit_err(2, "malloc err");
	curr = cmd;
	printf("get_cmd_argv \n START ---");
	token = curr->tokens->data;
	cmd_arg->argc = lst_size(curr->tokens);
	cmd_arg->argv = get_cmd_argv(curr->tokens);
	cmd_arg->fd[READ] = 0;
	cmd_arg->fd[WRITE] = 0;
	printf(" DONE ✅\n");
	return (cmd_arg);
}

int builtin_function(t_cmd *cmd, t_env *env)
{
	char *cmd_str;

	cmd_str = ((t_token *)cmd->tokens->data)->word;
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
	char		*str;
	t_env		*env;
	t_cmd_lst	*cmds;
	t_cmd_arg	*test;

	(void)argc;
	(void)argv;
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		add_history(str);
		cmds = (t_cmd_lst *)malloc(sizeof(t_cmd_arg));
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_FAILURE)
				exit_err(2, "Parse Error");
			print_cmds_list(cmds);
			test = parse_cmd_arg(cmds->cmd, env);
			int i = 0;
			printf("test->argc : [%d]\n", test->argc);
			printf("test->argv : ");
			while (test->argv[i])
			{
				printf(CYAN"[%s]"RESET, test->argv[i]);
				i++;
			}
			printf("\n");
			free(test);
		}
		free(str);
	}
	free(cmds);
	return (0);
}
