/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:12 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/21 22:28:21 by jisokang         ###   ########.fr       */
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
	printf("--------------"GREEN"[PRINT cmds list]"RESET"-------------\n");
	curr = cmds;
	i = 0;
	while (curr != NULL)
	{
		printf("cmd["BLUE"%d"RESET"]\n{\n", i++);
		curr2 = curr->cmd->tokens;
		while (curr2)
		{
			printf("\t");
			print_token(curr2->data);
			curr2 = curr2->next;
		}
		printf("}\n");
		curr = curr->next;
	}
	printf("--------------------------------------------\n");
	return (1);
}

int	parser(t_lst *tokens, t_cmd_lst **cmds)
{
	t_lst	*curr;
	t_cmd	*cmd;
	t_token	*token;

	if (tokens == NULL)
		return (0);
	curr = tokens;
	DEBUG && printf("--------------------"GREEN"PARSER"RESET"------------------\n");
	while (curr)
	{
		cmd = init_cmd();
		while (curr && ((t_token *)curr->data)->type != PIPE)
		{
			//dup_token() here
			token = init_token(((t_token *)curr->data)->type, ft_strdup(((t_token *)curr->data)->word));
			if (token->type == WORD)
			{
				DEBUG && printf("type:[%d]\tvalue:[%s]\n", token->type, token->word);
				lst_add_back(&cmd->tokens, lst_new((void *)token));
			}
			else
				lst_add_back(&cmd->rd, lst_new((void *)token));
			curr = curr->next;
		}
		cmd_lst_add_back(cmds, cmd_lst_new(cmd));
		if (curr)
			curr = curr->next;
	}
	DEBUG && printf("--------------------------------------------\n");
	return (EXIT_SUCCESS);
}
