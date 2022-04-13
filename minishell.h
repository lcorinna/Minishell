/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/13 22:04:42 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdlib.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h> 
# include <string.h>
# include <curses.h>
# include <term.h>

typedef	struct s_malloc
{
	/* Здесь хранятся указатели 
	на всю выделенную с помощью malloc память */
	
	/* Если malloc, сразу заносим сюда */

	char			*str;

}	t_malloc;

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;

}	t_llist;

typedef struct s_info
{
	// t_buildin_ptr	builtins[7]; //upd 13.04.: закоментил, а то компилятор ругался 
									// A: хранятся все билтины в этом массиве указателей на функции.
	char			*res_words[7];
	char			**envp;
	t_llist			envp_list;
	int				envp_f;
	int				exit_f;
	int				status;
	
	t_malloc		free_me;

}	t_info;

typedef int	(*t_buildin_ptr)(t_llist *, t_info *); //Д:не понимаю что это такое. upd 13.04.: закоментил, а то компилятор ругался
													// А:это указатель на функцию, которая принимает в себя два параметра типа t_llist* и t_info*,
													// а возвращает значение типа int.
													// Эта штука нужна для builin, которые ты пишешь.
													// см. комментарий выше... 

char	*ft_readline(const char *prompt, t_info *data);

#endif
