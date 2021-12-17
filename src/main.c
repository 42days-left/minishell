/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/14 18:29:56 by jisokang         ###   ########.fr       */
=======
/*   Updated: 2021/12/14 16:42:08 by yubae            ###   ########.fr       */
>>>>>>> 20955a4
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	main_loop(t_env *env)
{
	char		*str;
	t_cmd_lst	*cmds;

<<<<<<< HEAD
=======
	(void)argc;
	(void)argv;
	env = get_envp(envp);
	default_signal();
>>>>>>> 20955a4
	while(TRUE)
	{
		signal(SIGQUIT, SIG_IGN);
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
	set_signal();
	env = get_envp(envp);
	main_loop(env);
	return (0);
}
