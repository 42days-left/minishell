/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 15:22:50 by jisokang         ###   ########.fr       */
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
# include	"cmd.h"
# include	"token.h"
# include	"error.h"
# include	"builtin.h"
# include	"redir.h"
# include	"free.h"
# include	"parsing.h"
# include	"execute.h"
# include	"sort.h"

# define DEBUG		1

/* TYPE */
# define SCRIPT		0
# define COMMAND	1
# define WORD		2
# define PIPE		3
# define REDIR_L	4
# define REDIR_R	5
# define D_REDIR_L	6
# define D_REDIR_R	7

# define TRUE		1
# define FALSE		0
# define ERROR		-1
# define SAME		0

# define PATH_MAX	1024

# define BUF_SIZE	10000

# define READ		0
# define WRITE		1

# define EXIT_SYNTAXERR	2
# define EXIT_EXCUTE		126
# define EXIT_WRONGPATH	127

int		g_exitstat;

#endif
