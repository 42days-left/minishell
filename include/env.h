/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:06:29 by jisokang          #+#    #+#             */
/*   Updated: 2021/12/24 17:00:37 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define KEY	0
# define VALUE	1

# include "lst.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/* env_lst */
int		env_count(t_env *head);
t_env	*new_env_node(char *key, char *value);
t_env	*env_lst_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
void	env_lst_del(t_env *head, char *key);

/* env_print */
int		print_envp(char **envp);
void	print_envp_lst(t_env *head, int fd_out);

/* envp */
char	**env_to_envp(t_env *env);
void	free_envp(char **envp);
t_env	*get_env_from_str(char *str);
t_env	*get_envp(char **envp);

int		replace(t_lst *tokens, t_env *env);
char	*get_env_key_value(char *str);
char	*find_key_from_str(char *str_ptr);
int		is_valid_env_char(char c);
int		is_valid_key(char *key);
int		is_valid_key_value(char *key);
int		env_lst_size(t_env *head);
int		set_export_var(int argc, char **argv, t_env *env);

void	env_sort(t_env *head);
#endif
