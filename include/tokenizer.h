/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:10:55 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 16:11:39 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//int	convert_quote(char *script);
//int	reconvert_quote(char *str);
//int	convert_symbols(char *script, char *buf);
int	tokenizer(char *script, char ***strs);
