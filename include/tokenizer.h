/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:10:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/04 15:50:14 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

//int	convert_quote(char *script);
//int	reconvert_quote(char *str);
//int	convert_symbols(char *script, char *buf);
int	tokenizer(char *script, char ***strs);

#endif
