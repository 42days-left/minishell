/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:12 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/19 20:31:37 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->rd = NULL;
}

int	print_cmd(t_cmd *cmd)
{
	t_cmd	*curr;
	t_lst	*lst;

	printf("print_cmd_IN\n");
	curr = cmd;
	lst = curr->args;
	printf("print_cmd_OUT\n");


	return (0);
}

int	print_cmds_list(t_lst *cmds)
{
	t_lst	*curr;
	int		i;

	if (cmds == NULL)
	{
		printf("cmds is "MAGENTA"NULL\n"RESET);
		return (0);
	}
	printf("--------------"GREEN"[PRINT cmds list]"RESET"-------------\n");
	curr = cmds;
	curr = curr->next;
	i = 0;
	while(curr != NULL)
	{
		printf("cmd["BLUE"%d"RESET"]\n", i);
		//curr2 = (((t_cmd *)(curr->data))->args);
		printf("-----------\n");
		printf("1st-arg[%s]\n",/*  */ ((t_token *)((((t_cmd *)(curr->data))->args)->data))->arg /* */);
		//print_token_list(curr2);
		curr = curr->next;
		i++;
	}
	printf("--------------------------------------------\n");
	return (1);
}

int	parser(t_lst *tokens, t_lst **cmds)
{
	t_lst	*curr;
	t_cmd	*cmd;
	t_token	*token;

	curr = tokens;
	printf("parser()\t"BLUE"START"RESET"\n");
	while (curr)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->args = NULL;
		while (curr && ((t_token *)curr->data)->type != PIPE)
		{
			token = (t_token *)curr->data;
			if (token->type == WORD)
			{
				printf("this token\ttype:[%d]\tvalue:[%s]\n", token->type, token->arg);
				lst_add_back(&cmd->args, lst_new((void *)token));
				printf("---->[%s]\n", ((t_token *)(cmd->args)->data)->arg);
			}
			else
				lst_add_back(&cmd->rd, lst_new((void *)token));
			curr = curr->next;
		}
		lst_add_back(cmds, lst_new((void *)cmd));
		if (curr)
			curr = curr->next;
		free(cmd);
	}
	return (EXIT_SUCCESS);
}
