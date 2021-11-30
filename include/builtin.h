/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:12:41 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/30 19:55:30 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"lst.h"
# include	"env.h"

void	ft_cd(int argc, char **argv, t_env *env);
void	ft_env(t_env *env_lst);
void	ft_exit(int argc, char **argv);
int		ft_export(int argc, char **argv, t_env *env);
void	ft_pwd(void);
void	ft_echo(t_lst *cmds);
int		builtin_unset(int argc, char **argv, t_env *env);

#endif
