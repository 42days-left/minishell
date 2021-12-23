# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/30 15:48:36 by jisokang          #+#    #+#              #
#    Updated: 2021/12/23 15:42:15 by jisokang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FSAN	= -fsanitize=address
FLAGS	= -Wall -Wextra -Werror

DEBUG	= -fdiagnostics-color=always -g

#Cluster Mac
# CFLAGS	= -Iinclude -I/Users/$(USER)/.brew/opt/readline/include
# CLIB	= -L./lib/ -l_jisokang -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

#M1 Mac
CFLAGS	= -Iinclude -I/opt/homebrew/opt/readline/includ
CLIB	= -L./lib/ -l_jisokang -lreadline -L/opt/homebrew/opt/readline/lib

#YUBAE
#CFLAGS	= -Iinclude -I/usr/local/opt/readline/include
#CLIB	= -L./lib/ -l_jisokang -lreadline -L/usr/local/opt/readline/lib

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
	   execute/execute_path.c\
	   execute/execute_utils.c\
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

LIB_DIR = ./lib/

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	gcc $(DEBUG) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME)

re: fclean all

PHONY: all clean fclean re
