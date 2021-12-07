# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/12/07 17:39:04 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FSAN	= -fsanitize=address
CFLAGS	= -I include/ -I /Users/$(USER)/.brew/opt/readline/include -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

all :
	gcc -g $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
# gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
