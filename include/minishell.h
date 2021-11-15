/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:51 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/15 19:55:22 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <readline/readline.h> /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h> /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h> /* printf함수를 사용하기위한 헤더 */
# include <stdlib.h> /* free함수를 사용하기위한 헤더 */
# include <sys/stat.h>

# include "color.h"
# include "../lib/include/libft.h"
# include "env.h"
# include "tokenizer.h"

/* TYPE */
# define	SCRIPT	0
# define	COMMAND	1
# define	WORD	2
# define	PIPE	3
# define	REDIR_L 4
# define	REDIR_R 5
# define	D_REDIR_L 6
# define	D_REDIR_R 7

# define	TRUE	1
# define	FALSE	0

typedef struct s_lst
{
	void			*value;
	struct s_lst	*next;
}					t_lst;

typedef struct	s_token
{
	int			type;
	char		*arg;
}				t_token;

t_lst	*lst_new(void *value);
t_lst	*lst_init();
void	lst_insert(t_lst *before, t_lst *new);
void	lst_add_front(t_lst **lst, t_lst *new);
void	lst_add_back(t_lst **lst, t_lst *new);
void	lst_add_back_token(t_lst **lst, t_token *new);
void	print_lst_nul(t_lst *head);
int		lexer(char **strs, t_lst *tokens);

/*builtin*/

void	ft_exit(char *str);
void	ft_pwd(void);
char	*find_path(char *str, char **envp);
void	exec_child_process(char *str, char **envp);
int		exec_fork(char *str, char  **envp);
#endif


