# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/11/29 14:02:35 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FSAN	= -fsanitize=address
CFLAGS	= -I include/ -I /Users/$(USER)/.brew/opt/readline/include
CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

all :
	gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
