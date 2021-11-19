/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/19 14:12:56 by yubae            ###   ########.fr       */
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

# define	READ		0
# define	WRITE		1

/*builtin*/

void	ft_cd(char **envp);
void	ft_env(char **envp);
void	ft_exit(char *str);
void	ft_pwd(void);
char	*find_path(char *str, char **envp);
void	exec_child_process(t_tmp *tmp, char **envp);
int		exec_fork(char *str, char  **envp);
#endif


