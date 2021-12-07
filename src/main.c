/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/07 21:03:27 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	free_tokens(t_lst *tokens)
{
	t_lst	*curr;

	curr = tokens;
	while (curr)
	{
		// free(((t_token *)curr->data)->type);
		free(((t_token *)curr->data)->word);
		curr = curr->next;
	}
	lst_clear(tokens);
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	// free_tokens(&cmd->tokens);
	ft_lstclear2(&cmd->tokens, free_token_without_close);
	ft_lstclear2(&cmd->rd, free_token_without_close);
	free(cmd);
}

void	free_cmds(t_cmd_lst **lst)
{
	t_cmd_lst	*curr;
	t_cmd_lst	*next_lst;

	curr = *lst;
	while (curr != NULL)
	{
		next_lst = curr->next;
		free_cmd(curr);
		curr = next_lst;
	}
	*lst = NULL;
}

void	free_strings(char **strs)
{
	int i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * @param script string entered at the prompt
 */
int	parse(char *script, t_env *env, t_cmd_lst **cmds)
{
	t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	DEBUG && printf("script = \"%s\"\n", script);
	if(tokenizer(script, &strs))
		return (EXIT_FAILURE);
	tokens = NULL;
	lexer(strs, &tokens);
	DEBUG && print_token_list(tokens);
	replace(tokens, env);
	DEBUG && print_token_list(tokens);
	parser(tokens, cmds);
	free_strings(strs);
	ft_lstclear2(&tokens, free_token_without_close);
	//free_lst(tokens, free_token)
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_env		*env;
	t_cmd_lst	*cmds;

	(void)argc;
	(void)argv;
	set_signal();
	env = get_envp(envp);
	while(TRUE)
	{
		str = readline(MAGENTA"minihell🐚"RESET": ");
		printf("input = [%s]\n", str);
		add_history(str);
		if (!str)
			builtin_exit(1, NULL);
		cmds = (t_cmd_lst *)malloc(sizeof(t_cmd_arg));
		cmds = NULL;
		if (*str)
		{
			if (parse(str, env, &cmds) == EXIT_FAILURE)
				exit_err(2, "Parse Error");
			execute(cmds, env);
			printf(BLUE"[[%d]]\n"RESET, g_exitstat);
		}
		free(str);
		free_cmds(&cmds);
		// free(cmds);
	}
	return (0);
}
