# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 19:17:52 by lcorinna          #+#    #+#              #
#    Updated: 2022/04/09 17:00:59 by lcorinna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 NAME			=	minishell

FILES			=	test.c
					# main.c 			free_env.c		split.c			utils.c			\
					# main_utils.c	env.c			ft_itoa.c		utils_lst.c		\
					# ft_atoi.c		env_2.c			free_cmd.c		utils_str.c		\
					# fd_mem.c														\
					# 	builtins/builtins.c 		builtins/cd.c					\
					# 	builtins/unset.c			builtins/echo.c					\
					# 	builtins/pwd.c				builtins/export.c				\
					# 	builtins/env.c				builtins/exit.c					\
					# 	builtins/builtin_utils.c	builtins/export_utils.c			\
					# 																\
					# 	parse_main.c				parse_utils_cmd_token.c			\
					# 	parse_utils_token.c			parse_utils_cmd_list.c			\
					# 																\
					# lex_main.c				lex_general.c		lex_utils.c			\
					# lex_finisher_main.c 	lex_finisher.c		lex_check_token.c	\
					# 																\
					# exec_star.c				exec_cmd_list.c		exec_apply_1.c		\
					# exec_star_find_file.c	exec_cmd.c			exec_apply_2.c		\
					# exec_cmd_token_list.c	exec_cmd_utils.c	exec_utils.c		\
					# exec_cmd_list_check.c	ft_link.c			exec_utils_2.c

HOMEBREW_PREFIX := $(shell test -n "$$(which brew)" \
                        && brew config | grep HOMEBREW_PREFIX | cut -d' ' -f2)
						
SRC_PATH		=	./srcs/
SRC				=	$(addprefix $(SRC_PATH), $(FILES))
OBJ				=	$(SRC:.c=.o)
DEP				=	$(SRC:.c=.d)
INCLUDE			=	./includes
INCLUDE_SYS		=	$(HOMEBREW_PREFIX)/opt/readline/include
LIB_SYS			=	$(HOMEBREW_PREFIX)/opt/readline/lib

CFLAGS			=	-Wall -Werror -Wextra -MMD -g #-pedantic 
all				:	$(NAME)

bonus			:	all

$(NAME)			:	$(OBJ)
					cc $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -L$(LIB_SYS)

%.o				:	%.c
					cc $(CFLAGS) -c $< -o $@ -I$(LIB_SYS) -I$(INCLUDE_SYS)

clean			:
					rm -f $(OBJ) $(DEP)
fclean			:	clean
					rm -f $(NAME)
re				:	fclean all


-include $(DEP)

.PHONY			:	all clean fclean re

# cc -lreadline -I/Users/lcorinna/.brew/opt/readline/include -I/Users/lcorinna/.brew/opt/readline/lib -g -L/Users/lcorinna/.brew/opt/readline/lib ./srcs/test.c -o minishell

# -I каталог	-	Вызывает просмотр указанного каталога в поисках включаемых файлов, имена которых не начинаются с /, 
# перед просмотром стандартных каталогов. Если используется несколько опций -I, каталоги просматриваются в указанном порядке.

# -pedantic отключает дополнительные расширения и генерирует больше предупреждений. 
# Например, если у вас есть строковый литерал длиннее 509 символов, 
# то -pedanticвыдается предупреждение об этом, поскольку он превышает минимальное ограничение, требуемое стандартом C89
