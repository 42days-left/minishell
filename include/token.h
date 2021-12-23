/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:58:18 by yubae             #+#    #+#             */
/*   Updated: 2021/12/24 01:10:22 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lst.h"

void	default_signal(void);
void	on_signal(void);
void	off_echoctl(void);
void	signal_handler(int sig);
void	signal_handler_in_heredoc(int sig);

#endif
