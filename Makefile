# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: merlich <merlich@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 19:17:52 by lcorinna          #+#    #+#              #
#    Updated: 2022/05/03 23:14:41 by merlich          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M			=	minishell
#test.c
FILES			=	test.c envp.c	llist.c	ft_readline.c	exit.c	\
					lexer.c lexer_utils.c lexer_utils_2.c lexer_env_var.c \
					# ft_symsplit.c
					
					#
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

PATH_LIBFT		=	./libft/
LIBFT			=	libft.a

HOMEBREW_PREFIX	:=	$(shell test -n "$$(which brew)" \
						&& brew config | grep HOMEBREW_PREFIX | cut -d' ' -f2)
						
SRC_PATH		=	./srcs/
SRC				=	$(addprefix $(SRC_PATH), $(FILES))
OBJ				=	$(SRC:.c=.o)
DEP				=	$(SRC:.c=.d)
INCLUDE			=	./includes
INCLUDE_SYS		=	$(HOMEBREW_PREFIX)/opt/readline/include
LIB_SYS			=	$(HOMEBREW_PREFIX)/opt/readline/lib
CFLAGS			=	-Wall  -Wextra -MMD -g #-fsanitize=address #удобно сразу смотреть где читаем память мимо\
													# make && Leaks --atExit -- ./minishell
all				:	libmake $(NAME_M)

libmake			:
					make -C $(PATH_LIBFT)
					cp $(PATH_LIBFT)$(LIBFT) $(LIBFT)

bonus			:	all

$(NAME_M)			:	$(OBJ) ${LIBFT} #Д: это норм что в таких скобках?
					cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME_M) -lreadline -L$(LIB_SYS)

%.o				:	%.c Makefile
					cc $(CFLAGS) -c $< -o $@ -I$(LIB_SYS) -I$(INCLUDE_SYS)

clean			:
					rm -f $(OBJ) $(DEP) $(LIBFT)
					make clean -C $(PATH_LIBFT)

fclean			:	clean
					rm -f $(NAME_M)
					make fclean -C $(PATH_LIBFT)

re				:	fclean all


-include $(DEP)

.PHONY			:	all clean fclean re bonus

# cc -lreadline -I/Users/lcorinna/.brew/opt/readline/include -I/Users/lcorinna/.brew/opt/readline/lib -g -L/Users/lcorinna/.brew/opt/readline/lib ./srcs/test.c -o minishell

# -I каталог	-	Вызывает просмотр указанного каталога в поисках включаемых файлов, имена которых не начинаются с /, 
# перед просмотром стандартных каталогов. Если используется несколько опций -I, каталоги просматриваются в указанном порядке.
