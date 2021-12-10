# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/12/10 15:56:36 by yubae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FSAN	= -fsanitize=address
CFLAGS	= -I include/ -I /Users/$(USER)/.brew/opt/readline/include
	#-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include#
CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

all :
	gcc $(FSAN) $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
#	gcc $(CFLAGS) $(CLIB) ./src/*.c ./include/*.h
