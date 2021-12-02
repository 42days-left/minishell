/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/02 16:08:34 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<stdlib.h> /* free함수를 사용하기위한 헤더 */
# include	<readline/readline.h> /* readline함수를 사용하기위한 헤더 */
# include	<readline/history.h> /* add_history함수를 사용하기위한 헤더 */
# include	<sys/stat.h>

# include	<termios.h>

# include	"../lib/include/libft.h"
# include	"color.h"
# include	"lst.h"
# include	"env.h"
# include	"tokenizer.h"
# include	"cmd.h"
# include	"token.h"
# include	"error.h"
# include	"builtin.h"

# define	DEBUG		0

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
# define	ERROR		-1
# define	SAME		0

# define	BUF_SIZE	10000

# define	READ		0
# define	WRITE		1

void	set_signal(void);

int		execute(t_cmd_lst *cmds, t_env *env);

char	*find_path(char *str, t_env *env);
void	exec_child_process(char *str, t_env *env);
int		exec_fork(char *str, t_env  *env);
t_env	*find_env_from_env(char *in_key, t_env *env);
void	env_to_envp(t_env *env, char **envp);
int		print_envp(char **envp);
void	free_envp(char **envp);
int		env_count(t_env *env);

#endif


