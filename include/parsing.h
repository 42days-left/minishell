/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:12:26 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 17:17:12 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* PARSING TOKEN TYPE */
# define SCRIPT		0
# define COMMAND	1
# define WORD		2
# define PIPE		3
# define REDIR_L	4
# define REDIR_R	5
# define D_REDIR_L	6
# define D_REDIR_R	7

typedef struct s_token
{
	int		type;
	char	*word;
}			t_token;

/* lexer */
t_token	*init_token(int type, char *word);
int		lexer(char **strs, t_lst **tokens);

/* parser */
int		parser(t_lst *tokens, t_cmd_lst **cmds);
int		print_cmds_list(t_cmd_lst *cmds);

/* parsing */
int		parse(char *script, t_env *env, t_cmd_lst **cmds);
int		replace_env_token(t_token *token, t_env *env);
void	remove_quote_token(t_token *token);

/* print_token_list */
int		print_token(t_token *token);
int		print_token_list(t_lst *tokens, char *title_str);

/* replace */
t_env	*find_env_from_env(char *in_key, t_env *env);
int		replace(t_lst *tokens, t_env *env);

/* tokenizer */
int		tokenizer(char *script, char ***strs);

#endif
