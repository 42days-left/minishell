/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 17:18:27 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<fcntl.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<sys/stat.h>
# include	<termios.h>

# include	"../lib/include/libft.h"
# include	"color.h"
# include	"lst.h"
# include	"env.h"
# include	"cmd.h"
# include	"error.h"
# include	"builtin.h"
# include	"redir.h"
# include	"free.h"
# include	"parsing.h"
# include	"execute.h"
# include	"sort.h"
# include	"signal.h"

# define DEBUG			0

# define TRUE			1
# define FALSE			0
# define ERROR			-1
# define SAME			0

# define PATH_MAX		1024
# define BUF_SIZE		10000

# define READ			0
# define WRITE			1

/* EXIT STAUTS */
# define EXIT_SYNTAXERR	2
# define EXIT_EXCUTE	126
# define EXIT_WRONGPATH	127

int	g_exitstat;

#endif
