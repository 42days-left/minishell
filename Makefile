# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/12/19 17:51:55 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FSAN	= -fsanitize=address
#-I/opt/homebrew/opt/readline/include
FLAGS	= -Wall -Wextra -Werror

DEBUG	= -fdiagnostics-color=always -g

#Cluster Mac
#CFLAGS	= -Iinclude -I/Users/$(USER)/.brew/opt/readline/include
#CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

#M1 Mac
CFLAGS	= -Iinclude -I/opt/homebrew/opt/readline/includ
CLIB	= -L./lib/ -l_jisokang -lreadline -L/opt/homebrew/opt/readline/lib

FILE = cmd_arg.c cmd_lst.c error.c free.c lst.c main.c signal.c sort.c\
	   builtin/builtin.c\
	   builtin/builtin_cd.c\
	   builtin/builtin_echo.c\
	   builtin/builtin_env.c\
	   builtin/builtin_exit.c\
	   builtin/builtin_export.c\
	   builtin/builtin_pwd.c\
	   builtin/builtin_unset.c\
	   env/env_lst.c\
	   env/env_print.c\
	   env/envp.c\
	   execute/execute.c\
	   parsing/lexer.c\
	   parsing/parser.c\
	   parsing/parsing.c\
	   parsing/remove_quote.c\
	   parsing/replace.c\
	   parsing/tokenizer.c\
	   redir/get_redir_fd.c\
	   redir/here_doc.c\
	   redir/redirection.c

SRC_DIR = ./src
SRCS = $(addprefix $(SRC_DIR)/, $(FILE))

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	gcc $(DEBUG) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
