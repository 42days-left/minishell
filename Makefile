# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/12/14 18:41:34 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FSAN	= -fsanitize=address
CFLAGS	= -Iinclude -I/Users/$(USER)/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include
FLAGS	= -Wall -Wextra -Werror
# CFLAGS	= -I ./include/ -I /Users/$(USER)/.brew/opt/readline/include -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
# CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
CLIB	= -L./lib/ -l_jisokang -lreadline -L/opt/homebrew/opt/readline/lib

all :
	gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./src/*/*.c
#gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./src/builtin/*.c
# gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
