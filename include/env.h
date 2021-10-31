/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:06:29 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/31 19:36:47 by jisokang         ###   ########.fr       */
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

t_env	*new_env_node(char *key, char *value);
void	env_add_back(t_env **lst, t_env *new);
char	*search_env_lst(t_env **lst, char *key);

#endif
