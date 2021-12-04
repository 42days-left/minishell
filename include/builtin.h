/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:12:41 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/05 01:01:32 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include	"lst.h"
# include	"env.h"

int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_env(t_env *env, int fd_out);
int	builtin_exit(int argc, char **argv);
int	builtin_export(int argc, char **argv, t_env *env, int fd_out);
int	builtin_pwd(int fd_out);
int	builtin_unset(int argc, char **argv, t_env *env);
int	builtin_echo(int argc, char **argv, int fd);

#endif
