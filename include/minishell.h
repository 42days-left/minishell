/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/22 19:12:58 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<readline/readline.h> /* readline함수를 사용하기위한 헤더 */
# include	<readline/history.h> /* add_history함수를 사용하기위한 헤더 */
# include	<stdio.h> /* printf함수를 사용하기위한 헤더 */
# include	<stdlib.h> /* free함수를 사용하기위한 헤더 */
# include	<sys/stat.h>

# include	"../lib/include/libft.h"
# include	"color.h"
# include	"lst.h"
# include	"env.h"
# include	"tokenizer.h"
# include	"cmd.h"
# include	"token.h"
# include	"error.h"

/* TYPE */
# define	SCRIPT		0
# define	COMMAND		1
# define	WORD		2
# define	PIPE		3
# define	REDIR_L		4
# define	REDIR_R		5
# define	D_REDIR_L	6
# define	D_REDIR_R	7

# define	TRUE		1
# define	FALSE		0
# define	SAME		0

# define	BUF_SIZE	10000

# define	READ		0
# define	WRITE		1

/*builtin*/

void	ft_cd(t_cmd *cmd, t_env *env);
void	ft_env(t_env *env_lst);
void	ft_exit(char *str);
void	ft_export(t_cmd *cmd, t_env *env);
void	ft_pwd(void);
char	*find_path(char *str, t_env *env);
void	exec_child_process(char *str, t_env *env);
int		exec_fork(char *str, t_env  *env);
char	*find_value_from_env(char *in_key, t_env *env);
void	env_to_envp(t_env *env, char **envp);
int		print_envp(char **envp);
void	free_envp(char **envp);

#endif


