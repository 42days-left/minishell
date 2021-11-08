/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:19:36 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/08 13:04:37 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*int	parser(t_lst *tokens, t_lst *cmds)
{
	t_lst	*node;
	t_cmd	*cmd;
	t_token	*token;

	node = tokens->next;	//??? why?
	while (node)
	{
		//cmd = init_cmd();
		while (node && ((t_token *)node->data)->type != PIPE)
		{
			//token = dup_token()
			if (token->type == WORD)
				//push_lst() -> cmd->args
			else
				//push_lst() -> cmd->rd
			node = node->next;
		}
		//push_list(cmds, (void *)cmd);
		if (node)		//?? why???
			node = node->next;
	}
	return (EXIT_SUCCESS);
}*/
