# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/10/30 15:52:41 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :
	gcc -lreadline ./lib/lib_jisokang.a ./src/*.c ./include/*.h
