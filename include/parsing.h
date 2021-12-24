/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:12:26 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 17:03:17 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_token
{
	int		type;
	char	*word;
}			t_token;

int		tokenizer(char *script, char ***strs);
t_token	*init_token(int type, char *word);
int		lexer(char **strs, t_lst **tokens);
int		replace(t_lst *tokens, t_env *env);

int		parse(char *script, t_env *env, t_cmd_lst **cmds);
int		replace_env_token(t_token *token, t_env *env);
void	remove_quote_token(t_token *token);

int		print_token(t_token *token);
int		print_token_list(t_lst *tokens, char *title_str);

#endif
