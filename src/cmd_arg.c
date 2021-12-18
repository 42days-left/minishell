/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:07:16 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/18 14:26:05 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_cmd_arg(t_cmd_arg *cmd_arg)
{
	printf("===== PRINT_CMD_ARG =====\n");
	printf("argc:\t\t["BLUE"%d"RESET"]\n", cmd_arg->argc);
	printf("argv[0]:\t["BLUE"%s"RESET"]\n", cmd_arg->argv[0]);
	printf("fd_in:\t\t["BLUE"%d"RESET"]\n", cmd_arg->fd_in);
	printf("fd_out:\t\t["BLUE"%d"RESET"]\n", cmd_arg->fd_out);
	return (TRUE);
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
	return (str);
}

t_cmd_arg	*parse_cmd_arg(t_cmd *cmd, t_env *env, int fd_in, int fd_out)
{
	t_cmd		*curr;
	t_cmd_arg	*cmd_arg;
	t_token		*token;
	int			get_fd[2];

	cmd_arg = (t_cmd_arg *)malloc(sizeof(t_cmd_arg));
	if (!cmd_arg)
		exit_err(2, "malloc err");
	curr = cmd;
	token = curr->tokens->data;
	cmd_arg->argc = lst_size(curr->tokens);
	cmd_arg->argv = get_cmd_argv(curr->tokens);
	get_fd[0] = fd_in;
	get_fd[1] = fd_out;
	if (!get_redir_fd(curr->rd, get_fd))
	{
		free_cmd_arg(cmd_arg);
		return (NULL);
	}
	cmd_arg->fd_in = get_fd[0];
	cmd_arg->fd_out = get_fd[1];
	cmd_arg->env = env;
	return (cmd_arg);
}
