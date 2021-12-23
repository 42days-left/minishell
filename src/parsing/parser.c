/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:12 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 00:44:44 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof (t_cmd));
	if (!cmd)
		exit_err(EXIT_FAILURE, "Malloc Error");
	cmd->tokens = NULL;
	cmd->rd = NULL;
	return (cmd);
}

int	print_cmds_list(t_cmd_lst *cmds)
{
	t_cmd_lst	*curr;
	t_lst		*curr2;
	int			i;

	if (cmds == NULL)
		return (0);
	printf("\n["GREEN"CMDS LIST"RESET"]\n{\n");
	curr = cmds;
	i = 0;
	while (curr != NULL)
	{
		printf("\tcmd["BLUE"%d"RESET"]\n\t{\n", i++);
		curr2 = curr->cmd->tokens;
		while (curr2)
		{
			printf("\t\t");
			print_token(curr2->data);
			curr2 = curr2->next;
		}
		printf("\t}\n");
		curr = curr->next;
	}
	printf("{\n");
	return (1);
}

t_token	*get_token_from_lst(t_lst *curr)
{
	t_token	*token;
	t_token	*cdata;

	cdata = curr->data;
	token = init_token(cdata->type, ft_strdup(cdata->word));
	return (token);
}

int	parser(t_lst *tokens, t_cmd_lst **cmds)
{
	t_lst	*curr;
	t_cmd	*cmd;
	t_token	*token;

	if (tokens == NULL)
		return (0);
	curr = tokens;
	while (curr)
	{
		cmd = init_cmd();
		while (curr && ((t_token *)curr->data)->type != PIPE)
		{
			token = get_token_from_lst(curr);
			if (token->type == WORD)
				lst_add_back(&cmd->tokens, lst_new(token));
			else
				lst_add_back(&cmd->rd, lst_new(token));
			curr = curr->next;
		}
		cmd_lst_add_back(cmds, cmd_lst_new(cmd));
		if (curr)
			curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
