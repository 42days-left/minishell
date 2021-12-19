/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:10:07 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/19 19:55:51 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_arg(t_cmd_arg *ca);
void	free_tokens(t_lst *tokens);
void	free_cmd(void *data);
void	free_cmds(t_cmd_lst **lst);
void	free_strings(char **strs);


void	free_tokens_parse(t_lst *lst);
