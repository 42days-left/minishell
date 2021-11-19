/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:12 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/19 15:59:47 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->rd = NULL;
}

int	parser(t_lst *tokens, t_lst *cmds)
{
	t_lst	*curr;
	t_cmd	*cmd;
	t_token	*token;

	curr = tokens;
	cmd = NULL;
	printf("parser()\t"BLUE"START"RESET"\n");
	while (curr)
	{
		//init_cmd(cmd);
		printf("while(curr)\t"BLUE"START"RESET"\n");
		//lst_init();
		//cmd->rd = NULL;
		printf("init_cmd()\t"GREEN"Done"RESET"\n");
		while (curr && ((t_token *)curr->value)->type != PIPE)
		{
			printf("while(curr&&pipe)\t"BLUE"START"RESET"\n");
			token = curr->value;
			printf("token get value\t"GREEN"Done"RESET"\n");
			if (token->type == WORD)
			{
				printf("WOW! I found WORD\t"GREEN"Done"RESET"\n");
				lst_add_back(&cmd->args, lst_new(token));
				printf("lst_add_back\t"GREEN"Done"RESET"\n");
			}
			else
				lst_add_back(&cmd->rd, lst_new((void *)token));
			curr = curr->next;
		}
		lst_add_back(&cmds, lst_new((void *)cmd));
		if (curr)
			curr = curr->next;
	}
	printf("parser() "BLUE"END"RESET"\n");
	return (EXIT_SUCCESS);
}
