/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 14:30:13 by lcorinna         ###   ########.fr       */
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

// # define SPACE			0
# define WORD			1
# define FIELD			2
# define EXP_FIELD		3
# define REDIR_OUT		4
# define REDIR_IN		5
# define REDIR_APPEND	6
# define REDIR_INSOURCE	7
# define PIPE			8
# define IF_AND			9
# define IF_OR			10
# define PARN_L			11
# define PARN_R			12

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
	t_llist			*envp_list;
	int				envp_f;
	int				exit_f;
	int				status;

	t_malloc		free_me;

}	t_info;

typedef int	(*t_buildin_ptr)(t_llist *, t_info *); //Д:не понимаю что это такое.
													// А:это указатель на функцию, которая принимает в себя два параметра типа t_llist* и t_info*,
													// а возвращает значение типа int.
													// Эта штука нужна для builin, которые ты пишешь.
													// см. комментарий выше... 

typedef struct s_token
{
	char			*str_val;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;

}	t_token;

char	*ft_malloc(int size);
void	ft_envp(char **envp, t_info *data);
void	ft_envp2(char *envp, char *key, char *value);

t_llist	*ft_lstnew(void *key, void *value);
void	ft_lstadd_front(t_llist **lst, t_llist *new);
t_llist	*ft_lstlast(t_llist *lst);
void	ft_lstadd_back(t_llist **lst, t_llist *new);

void	ft_readline(const char *prompt, t_info *data);

#endif
