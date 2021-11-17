/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:27:11 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/17 15:16:50 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//void	remove_quote_token(t_token *token)
//{
//	char	buf[BUF_SIZE];
//	char	*str;
//	int		i;

//	str = token->arg;
//	i = 0;
//	while (str[i] != '\0')
//	{
//		while (str[i] == '\"' || str[i] == '\'')
//			i++;
//		buf[i] = str[i];
//		i++;
//	}
//	buf[i] = '\0';
//	free(token->arg);
//	token->arg = ft_strdup(buf);
//}
