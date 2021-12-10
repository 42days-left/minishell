/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>:           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:25:19 by yubae             #+#    #+#             */
/*   Updated: 2021/11/29 18:52:24 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dot_path(char *path)
{
	if (path[0] == '.')
	{
		if (path[1] == '\0')
			exit_err(EXIT_SYNTAXERR, ".: filename argument required");
		else if (path[1] == '.' && path[2] == '\0')
			exit_err(EXIT_WRONGPATH, "..: command not found");
	}
}

char *find_path(char *in_path, t_env *env)
{
	int		i;
	t_env	*tmp;
	char	*new_path;
	char	**path_arr;
	struct stat s;

	tmp = find_env_from_env("PATH", env);
	path_arr = ft_split(tmp->value, ':');
	DEBUG && printf("----------------"GREEN"FIND NEW_PATH"RESET"---------------\n");
	if (!stat(in_path, &s))
	{
		check_dot_path(in_path);
		if ((s.st_mode & S_IFMT) == S_IFDIR)
		{
			printf(YELLOW"%s: "RESET, in_path);
			exit_err(EXIT_EXCUTE, "is a directory");
		}
		return(in_path);
	}
	if (in_path[0] == '/')
	{
		printf(YELLOW"%s: "RESET, in_path);
		exit_err(EXIT_WRONGPATH, "No such file or directory");
	}
	i = 0;
	while(path_arr[i])
	{
		tmp->value = ft_strjoin("/", in_path);
		new_path = ft_strjoin(path_arr[i], tmp->value);
		free(tmp->value);
		free(tmp);
		DEBUG && printf("\tnew_path ["MAGENTA"%d"RESET"] : ["MAGENTA"%s"RESET"]\n", i, new_path);
		if (!stat(new_path, &s))
		{
			DEBUG && printf("-----------------------------------FIND_"GREEN"DONE"RESET"\n");
			return (new_path);
		}
		free(new_path);
		i++;
	}
	DEBUG && printf("-----------------------------------FIND_"RED"FAIL"RESET"\n");
	return (NULL);
}

void	exec_child_process2(t_cmd_arg *ca)
{
	char *path;
	char **envp;
	int	cnt;

	DEBUG && printf("exec_child_process()\t"GREEN"START"RESET"\n");
	envp = env_to_envp(ca->env);
	path = find_path(ca->argv[0], ca->env);
	if (path != NULL)
		execve(path, ca->argv, envp);
	else
	{
		printf(YELLOW"%s"RESET, ca->argv[0]);
		exit_err(EXIT_WRONGPATH, ": command not found");
	}
	free(path);
	free_envp(envp);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Get the WEXITSTATUS object
 *
 * @param stat
 * @return int
 */
static int	get_wexitstat(int stat)
{
	return ((((*(int *)&(stat)) >> 8) & 0x000000ff));
}

int	exec_fork2(t_cmd_arg *cmd_arg)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_child_process2(cmd_arg);
		return(1);
	}
	waitpid(pid, &status, 0);
	g_exitstat = get_wexitstat(status);
//	close(fd[1]);
//	close(fd[0]);
	return (EXIT_SUCCESS);
}

int extern_function(t_cmd_arg *ca)
{
	exec_fork2(ca);
	return (EXIT_SUCCESS);
}

int builtin_function(t_cmd_arg *ca)
{
	if (!ft_strncmp(ca->argv[0], "pwd", 4))
		g_exitstat = builtin_pwd(ca->fd[WRITE]);
	else if (!ft_strncmp(ca->argv[0], "exit", 5))
		g_exitstat = builtin_exit(ca->argc, ca->argv);
	else if (!ft_strncmp(ca->argv[0], "echo", 5))
		g_exitstat = builtin_echo(ca->argc, ca->argv, ca->fd[WRITE]);
	else if (!ft_strncmp(ca->argv[0], "env", 4))
		g_exitstat = builtin_env(ca->env, ca->fd[WRITE]);
	else if (!ft_strncmp(ca->argv[0], "export", 7))
		g_exitstat = builtin_export(ca->argc, ca->argv, ca->env, ca->fd[WRITE]);
	else if (!ft_strncmp(ca->argv[0], "unset", 6))
		g_exitstat = builtin_unset(ca->argc, ca->argv, ca->env);
	else if (!ft_strncmp(ca->argv[0], "cd", 3))
		g_exitstat = builtin_cd(ca->argc, ca->argv, ca->env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute1(t_cmd_lst *cmds, t_env *env)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = parse_cmd_arg(cmds->cmd, env);
	if (builtin_function(cmd_arg))
		extern_function(cmd_arg);
	return (EXIT_SUCCESS);
}

int	execute2(t_cmd_lst *cmds, t_env *env)
{
	return (0);
}

int	execute(t_cmd_lst *cmds, t_env *env)
{
	int				count;
	t_cmd_lst		*curr;

	curr = cmds;
	// count = lst_size(curr);
	count = 1;
	if (count == 1)
		execute1(cmds, env);
	else
	 	execute2(cmds, env);
	return (1);
}
