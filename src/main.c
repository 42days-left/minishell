/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 13:17:04 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;
	t_cmd_lst	*cmds;

	(void)argc;
	(void)argv;
	set_signal();
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		add_history(str);
		if (!str)
			builtin_exit(1, NULL);
		cmds = (t_cmd_lst *)malloc(sizeof(t_cmd_arg));
		if (!cmds)
			exit_err(2, "Malloc Error");
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_FAILURE)
				exit_err(2, "Parse Error");
			execute(cmds, env);
		}
		free(str);
		//free_cmds(&cmds);
		//free(cmds);
	}
	return (0);
}
