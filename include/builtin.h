/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:12:41 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/04 16:30:15 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"lst.h"
# include	"env.h"

int		ft_cd(int argc, char **argv, t_env *env);
int		builtin_env(t_env *env_lst);
int		builtin_exit(int argc, char **argv);
int		ft_export(int argc, char **argv, t_env *env);
int		ft_pwd(int fd_out);
int		builtin_unset(int argc, char **argv, t_env *env);
int		builtin_echo(int argc, char **argv, int fd);

#endif
