/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/17 21:13:44 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	main_loop(t_env *env)
{
	char		*str;
	t_cmd_lst	*cmds;

	while(TRUE)
	{
		// signal(SIGQUIT, SIG_IGN);
		str = readline(MAGENTA"minihell🐚"RESET": ");
		if (!str)
			builtin_exit(1, NULL);
		add_history(str);
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
		free_cmds(&cmds);
		//free(cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = get_envp(envp);
	// default_signal();
	main_loop(env);
	return (0);
}
