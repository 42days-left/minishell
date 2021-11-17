/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/17 14:53:34 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<readline/readline.h> /* readline함수를 사용하기위한 헤더 */
# include	<readline/history.h> /* add_history함수를 사용하기위한 헤더 */
# include	<stdio.h> /* printf함수를 사용하기위한 헤더 */
# include	<stdlib.h> /* free함수를 사용하기위한 헤더 */

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
# define	SAME		0

# define	BUF_SIZE	10000

#endif


