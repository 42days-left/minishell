/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devleo <devleo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:46:09 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/28 00:31:25 by devleo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

typedef struct s_lst
{
	void			*data;
	struct s_lst	*next;
}					t_lst;

t_lst	*lst_new(void *value);
t_lst	*lst_init();
void	lst_clear(t_lst *head);
int		lst_size(t_lst *head);
void	lst_insert(t_lst *before, t_lst *new);
void	lst_add_front(t_lst **lst, t_lst *new);
void	lst_add_back(t_lst **lst, t_lst *new);
void	print_lst_nul(t_lst *head);

#endif
