/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:06:29 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 15:48:49 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define KEY	0
# define VALUE	1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

int		print_envp(char **envp);
t_env	*new_env_node(char *key, char *value);
t_env	*env_lst_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
char	*search_env_lst(t_env **lst, char *key);
char	*get_env_key_value(char *str);
int		get_envp(char **envp);

#endif
