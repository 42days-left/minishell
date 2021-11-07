/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/07 22:50:01 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE		1

/*
typedef struct	s_token
{
	int			type;
	char		*value;
}				t_token;
*/

/*
typedef struct	s_cmd
{
	t_lst	*args;
	t_lst	*rd;
}			t_cmd;
*/

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


/**
 * @param script string entered at the prompt
 */
int	parse(char *script, t_env *env, t_lst *cmds)
{
	t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	//tokens = lst_init();
	tokens = NULL;
	lexer(strs, tokens);
	printf("1st tokens [%s]\n", ((t_token *)(tokens->value))->arg);

	//print_token_list(tokens);
	//replace_env(tokens);
	//parser(tokens, cmds);

	//free_strings(strs)
	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;
	t_lst	*cmds;

	(void)argc;
	(void)argv;
	print_envp(envp);
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		cmds = lst_init();
		if (str)
		{
			printf("input\t: %s\n", str);
			parse(str, env, cmds);
			/*!!!!!!!!!!!!!!!!!*/
			//execute(cmds, env);
			/*!!!!!!!!!!!!!!!!!*/
		}
		else
			break ;
		add_history(str);
		free(str);
	}
	return(0);
}
