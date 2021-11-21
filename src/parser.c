/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:12 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/21 17:03:30 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->rd = NULL;
}

int	print_cmds_list(t_lst *cmds)
{
	t_lst	*curr;
	t_lst	*curr2;
	int		i;

	if (cmds == NULL)
	{
		printf("cmds is "MAGENTA"NULL\n"RESET);
		return (0);
	}
	printf("--------------"GREEN"[PRINT cmds list]"RESET"-------------\n");
	curr = cmds;
	i = 0;
	while(curr != NULL)
	{
		printf("cmd["BLUE"%d"RESET"]\n{\n", i++);
		curr2 = ((t_cmd *)(curr->data))->args;
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

int	parser(t_lst *tokens, t_lst **cmds)
{
	t_lst	*curr;
	t_cmd	*cmd;
	t_token	*token;

	if (tokens == NULL)
		return (0);
	curr = tokens;
	while (curr)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->args = NULL;
		cmd->rd = NULL;
		while (curr && ((t_token *)curr->data)->type != PIPE)
		{
			token = (t_token *)curr->data;
			if (token->type == WORD)
			{
				printf("this token\ttype:[%d]\tvalue:[%s]\n", token->type, token->arg);
				lst_add_back(&cmd->args, lst_new((void *)token));
			}
			else
				lst_add_back(&cmd->rd, lst_new((void *)token));
			curr = curr->next;
		}
		lst_add_back(cmds, lst_new((void *)cmd));
		if (curr)
			curr = curr->next;
	}
	free(cmd);
	return (EXIT_SUCCESS);
}
