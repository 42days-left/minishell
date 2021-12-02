/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:07:16 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/02 16:38:46 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	cmd_arg = (t_cmd_arg *)malloc(sizeof(t_cmd_arg));
	if (!cmd_arg)
		exit_err(2, "malloc err");
	curr = cmd;
	token = curr->tokens->data;
	cmd_arg->argc = lst_size(curr->tokens);
	cmd_arg->argv = get_cmd_argv(curr->tokens);
	cmd_arg->fd[READ] = STDIN_FILENO;
	cmd_arg->fd[WRITE] = STDOUT_FILENO;
	cmd_arg->env = env;
	return (cmd_arg);
}
