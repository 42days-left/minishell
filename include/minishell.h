/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/14 16:25:37 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include	<unistd.h>
# include	<fcntl.h>
# include	<stdio.h>
# include	<stdlib.h> /* free함수를 사용하기위한 헤더 */
# include	<unistd.h>
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
# include	"redirect.h"

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

# define	PATH_MAX	1024

# define	BUF_SIZE	10000

# define	READ		0
# define	WRITE		1

# define	EXIT_SYNTAXERR	2
# define	EXIT_EXCUTE		126
# define	EXIT_WRONGPATH	127

void	default_signal(void);
void	on_signal(void);
void	off_signal(void);
void	on_echoctl(void);
void	off_echoctl(void);
void	signal_handler(int sig);

/*builtin*/

void		execute(t_cmd_lst *cmds, t_env *env);
void	free_strings(char **strs);

char	*find_path(char *in_path, t_env *env);
void	exec_child_process(char *str, t_env *env);
int		exec_fork(char *cmd_name, t_env  *env);
t_env	*find_env_from_env(char *in_key, t_env *env);
char	**env_to_envp(t_env *env);
int		print_envp(char **envp);
void	free_envp(char **envp);
int		env_count(t_env *env);

int		g_exitstat;

#endif


