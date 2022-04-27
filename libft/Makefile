# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: merlich <merlich@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 18:20:29 by merlich           #+#    #+#              #
#    Updated: 2022/04/27 22:33:50 by merlich          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a

SRCS		=	ft_strlen.c	ft_putstr_fd.c	ft_split.c	ft_strtrim.c \
				ft_strjoin.c ft_strdup.c ft_strchr.c ft_substr.c \
				ft_isalpha.c ft_isalpha_big.c ft_isdigit.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
 				ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
 				ft_toupper.c ft_tolower.c  ft_strrchr.c \
 				ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
 				ft_atoi.c ft_calloc.c ft_strdup.c  \
 				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
 				ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
 				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

# SRCS_BONUS 	= 	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
# 				ft_lstsize_bonus.c \
# 				ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
# 				ft_lstdelone_bonus.c ft_lstclear_bonus.c \
# 				ft_lstiter_bonus.c ft_lstmap_bonus.c

D_FILES		=	${SRCS:.c=.d} ${SRCS_BONUS:.c=.d}

HEADER 		= 	libft.h

OBJS 		= 	${SRCS:.c=.o}

OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}

BONUS 		= 	bonus

CLANG 		= 	clang

CFLAGS 		= 	-Wall -Wextra -Werror -MD

RM 			= 	rm -f

%.o:		%.c Makefile
			${CLANG} ${CFLAGS} -c $< -o $@

all:		${NAME}

$(NAME): 	${OBJS}
			ar rcs ${NAME} $?

-include $(D_FILES)

$(BONUS):	
			@make OBJS="${OBJS_BONUS}" all

clean:		
			${RM} ${OBJS} ${OBJS_BONUS} ${D_FILES}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
