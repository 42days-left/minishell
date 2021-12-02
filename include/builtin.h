/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:12:41 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/02 16:37:56 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"lst.h"
# include	"env.h"

int		ft_cd(int argc, char **argv, t_env *env);
void	ft_env(t_env *env_lst);
void	ft_exit(int argc, char **argv);
int		ft_export(int argc, char **argv, t_env *env);
int		ft_pwd(int fd_out);
void	ft_echo(t_lst *cmds);
int		builtin_unset(int argc, char **argv, t_env *env);
int		builtin_echo(int argc, char **argv);

#endif
