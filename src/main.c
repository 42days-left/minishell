/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 22:29:36 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logo(void)
{
	printf(\
RED "______  ________________   ________________  __________________ ______ \n"\
BLUE"___   |/  /____  _/___  | / /____  _/___  / / /___  ____/___  / ___  / \n"\
RED "__  /|_/ /  __  /  __   |/ /  __  /  __  /_/ / __  __/   __  /  __  /  \n"\
BLUE"_  /  / /  __/ /   _  /|  /  __/ /   _  __  /  _  /___   _  /____  /___\n"\
RED "/_/  /_/   /___/   /_/ |_/   /___/   /_/ /_/   /_____/   /_____//_____/\n"\
BLUE"                                                      @yubae @jisokang \n"\
	RESET);
}

static t_cmd_lst	*init_cmd_lst(void)
{
	t_cmd_lst	*cmds;

	cmds = (t_cmd_lst *)malloc(sizeof(t_cmd_arg));
	if (!cmds)
		exit_err(EXIT_FAILURE, "Malloc Error");
	cmds->cmd = NULL;
	cmds->next = NULL;
	return (cmds);
}

void	free_cmd_lst(t_cmd_lst *cmds)
{
	t_cmd_lst	*curr;
	t_cmd_lst	*next_lst;
	t_lst		*tokens;
	t_lst		*rd;

	if (!cmds)
		return ;
	curr = cmds;
	while (curr != NULL)
	{
		next_lst = curr->next;
		if (curr->cmd)
		{
			tokens = curr->cmd->tokens;
			if (tokens)
				free_tokens_parse(tokens);
			rd = curr->cmd->rd;
			if (rd)
				free_tokens_parse(rd);
		}
		free(curr->cmd);
		free(curr);
		curr = next_lst;
	}
	cmds = NULL;
}

void	main_loop(t_env *env)
{
	char		*str;
	t_cmd_lst	*cmds;

	while (TRUE)
	{
		default_signal();
		str = readline("minihell🐚: ");
		if (!str)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
			add_history(str);
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_SUCCESS)
				execute(cmds, env);
		}
		free(str);
		free_cmd_lst(cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = get_envp(envp);
	default_signal();
	logo();
	main_loop(env);
	return (0);
}
