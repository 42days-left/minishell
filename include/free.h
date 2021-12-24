/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:10:07 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 14:51:17 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

void	free_cmd_arg(t_cmd_arg *ca);
void	free_tokens(t_lst *tokens);
void	free_cmd(void *data);
void	free_cmds(t_cmd_lst **lst);
void	free_strings(char **strs);

void	free_tokens_parse(t_lst *lst);
void	free_env_node(t_env *node);

#endif
