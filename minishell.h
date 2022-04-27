/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/27 21:27:27 by merlich          ###   ########.fr       */
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

# define SPACES			" \f\n\r\t\v"
# define QUOTES			"\'\""
# define LEXER_ERROR	101
# define UNDEFINED		-1
# define IS_SPACE		0
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

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;

}	t_llist;

typedef	struct s_malloc
{
	/* Здесь хранятся указатели 
	на всю выделенную с помощью malloc память */

	/* Если malloc, сразу заносим сюда */

	char			*str;

}	t_malloc;

typedef struct s_token
{
	char			*str_val;
	int				type;
	int				in_quotes;
	struct s_token	*next;
	struct s_token	*prev;

}	t_token;

typedef struct s_info
{
	// t_buildin_ptr	builtins[7]; //upd 13.04.: закоментил, а то компилятор ругался 
									// A: хранятся все билтины в этом массиве указателей на функции.
	char			*res_words[7];
	char			**envp;
	t_llist			*envp_list; //функция для чистки ft_clean_envp_list
	char			**path;
	pid_t			pid;
	int				envp_f;
	int				exit_f;
	int				status;
	t_token			*tokens;

	t_malloc		free_me;

}	t_info;

typedef int	(*t_buildin_ptr)(t_llist *, t_info *); //Д:не понимаю что это такое.
													// А:это указатель на функцию, которая принимает в себя два параметра типа t_llist* и t_info*,
													// а возвращает значение типа int.
													// Эта штука нужна для builin, которые ты пишешь.
													// см. комментарий выше... 



void		ft_array_envp(t_info *data);
int			ft_envp2(char *envp, char **key, char **value, int j);
void		ft_envp(t_info *data);
void		ft_transfer(int argc, char **argv, char **envp, t_info *data);

t_llist		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_llist **lst, t_llist *new);
t_llist		*ft_lstlast(t_llist *lst);
void		ft_lstadd_back(t_llist **lst, t_llist *new);

void		ft_readline(t_info *data);

int			ft_cleaning_str(char *str);
int			ft_cleaning_array(char **arr);
void		ft_clean_envp_list(t_info *data);
void		ft_clean_struct(t_info *data);
void		ft_error_exit(t_info *data, int i);

/* lexer.c */
int			ft_get_tokens(char *str, t_info *data);
void		ft_set_tokens_type(t_info *data);


/* lexer_utils.c */
t_token		*ft_token_lstnew(char *value);
int			ft_token_lstsize(t_token *head);
t_token		*ft_token_lstlast(t_token *head);
void		ft_token_lstadd_front(t_token **head, t_token *new);
void		ft_token_lstadd_back(t_token **head, t_token *new, int in_quotes);

/* lexer_utils_2.c */
t_token		*ft_token_last_but_one(t_token *head);
void		ft_token_dellast(t_token **head);
void		ft_token_lstclear(t_token **head);

#endif
