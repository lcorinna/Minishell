# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 19:17:52 by lcorinna          #+#    #+#              #
#    Updated: 2022/05/28 17:49:45 by lcorinna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M			=	minishell

FILES			=	minishell.c \
					envp.c llist.c ft_readline.c exit.c \
					lexer.c lexer_utils.c lexer_utils_2.c lexer_utils_3.c \
					lexer_env_var.c ft_handle_symbols.c \
					parser.c parser_cmd_utils.c parser_group_utils.c \
					ft_check_redir_insource.c ft_check_redir_in.c \
					ft_check_redir_out.c ft_check_redir_append.c \
					ft_check_words.c ft_perror.c \
					bin_tree.c bin_tree_utils.c bin_tree_branches_utils.c \
					wildcards.c checkers.c \
					executor.c executor_one_cmd.c executor_many_cmd.c \
					executor_utils.c builtins/builtin_utils.c builtins/b_pwd.c \
					builtins/b_cd.c builtins/b_cd_utils.c builtins/b_unset.c \
					builtins/b_echo.c builtins/b_env.c builtins/b_exit.c \
					builtins/b_export.c builtins/b_export_print.c \
					builtins/b_export_utils.c signal.c\
				

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
CFLAGS			=	-Wall -Wextra  -MMD -g -fsanitize=address #удобно сразу смотреть где читаем память мимо\
													# make && Leaks --atExit -- ./minishell
all				:	libmake $(NAME_M)

libmake			:
					make -C $(PATH_LIBFT)
					cp $(PATH_LIBFT)$(LIBFT) $(LIBFT)

bonus			:	all

$(NAME_M)		:	$(OBJ) $(LIBFT)
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
