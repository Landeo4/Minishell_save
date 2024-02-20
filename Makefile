# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:22:06 by vsozonof          #+#    #+#              #
#    Updated: 2024/02/19 14:27:10 by tpotilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -g3

BL=\033[1;34m
GR=\033[1;32m
OR=\033[1;33m
RD=\033[1;31m
WH=\033[0m

SRCS_LIB = libft/libft.a \

SRCS = main.c \
	   parsing/get_input.c \
	   parsing/init/init_master.c \
	   parsing/input_parser.c \
	   parsing/exception_checker.c \
	   parsing/redirs/redir_utils-1.c \
	   parsing/redirs/redir_utils-2.c \
	   parsing/redirs/redir_utils-3.c \
	   parsing/redirs/redir_utils-4.c \
	   parsing/redirs/redir_utils-5.c \
	   parsing/expand/expand_master.c \
	   parsing/expand/expand_utils-1.c \
	   parsing/expand/expand_utils-2.c \
	   parsing/pipes/pipe_splitter.c \
	   parsing/pipes/pipe_utils-1.c \
	   parsing/pipes/pipe_utils-2.c \
	   parsing/env/env_utils-1.c \
	   parsing/env/env_utils-2.c \
	   free/free_master.c \
	   free/free_utils-1.c \
	   utils/exit_status.c \
	   utils/quote_utils-1.c \
	   utils/args_counter.c \
	   signal/signal_master.c \
	   exec/command_manager.c \
	   exec/UNUSED_command_overall.c \
	   exec/execute_pp.c \
	   exec/main_pp.c \
	   exec/heredoc.c \
	   exec/pp_free.c \
	   exec/pp_free2.c \
	   exec/pp_utils.c \
	   exec/pp_utils2.c \
	   exec/pp_utils3.c \
	   exec/pp.c \
	   exec/pp_helper.c \
	   exec/single_arg.c \
	   exec/child_pp.c \
	   exec/redirection_here.c \
	   exec/redirection_found.c \
	   exec/redirection_arg.c \
	   exec/redirection_dup.c \
	   exec/here_doc.c \
	   builtin/unset/unset_master.c \
	   builtin/unset/unset_utils-1.c \
	   builtin/cd/cd_master.c \
	   builtin/cd/cd_utils-1.c \
	   builtin/echo/echo_master.c \
	   builtin/export/export_master.c \
	   builtin/export/export_utils-1.c \
	   builtin/export/export_utils-2.c \
	   builtin/export/export_utils-3.c \
	   builtin/pwd/pwd_master.c \
	   builtin/env/env_master.c \
	   builtin/exit/exit.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: init $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(RD)MINISHELL -\t$(WH)$(BL)Linking $(OR)($<)$(WH)\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(SRCS_LIB)
	@echo "                                   \r\c"

%.o: %.c
	@echo "$(RD)MINISHELL -\t$(WH)$(BL)Compiling $(OR)($<)$(WH)\c\r"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "                                   \r\c"

init:
	make all -C ./libft

clean:
		make clean -C ./libft
		@$(RM) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files were deleted !$(WH)"

fclean: 
		make fclean -C ./libft
		@$(RM) $(NAME) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files and binaries were deleted !$(WH)"

re: fclean all

.PHONY: all clean fclean re init