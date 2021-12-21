/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubae <yubae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:39:12 by yubae             #+#    #+#             */
/*   Updated: 2021/12/21 20:48:21 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

void	execute(t_cmd_lst *cmds, t_env *env);

char	*find_path(char *in_path, t_env *env);

int	get_wexitstat(int stat);
int	ft_dup(int fd1, int fd2);
int	wait_cmds(int last_pid);

#endif