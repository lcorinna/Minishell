/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/17 17:08:11 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h> 
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>

# define SHELL			"minishell$ "
# define HEREDOC		".here_doc"
# define SPACES			" \f\n\r\t\v"
# define QUOTES			"\'\""
# define SYMBOLS		"<|>()&"
# define LOGIC_OPER		"&|"
# define NOT_FIRST		")|&"
# define LEXER_ERROR	101
# define SYMBOLS_ERROR	102
# define UNDEFINED		-1
// # define IS_SPACE		0
# define WORD			1
// # define FIELD			2
// # define EXP_FIELD		3
# define REDIR_OUT		4
# define REDIR_IN		5
# define REDIR_APPEND	6
# define REDIR_INSOURCE	7
# define PIPE			8
# define AND			13
# define IF_AND			9
# define IF_OR			10
# define PARN_L			11
# define PARN_R			12
// # define MALLOC			ENOMEM  // Уже есть такая штука в stdlib.h. Используй её.
# define DUP			81

typedef struct s_cmds
{
	int				infile;
	int				outfile;
	char			*cmd_path;
	char			*cmd_argv;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_group
{
	t_cmds			*cmds_head;
	int				logical_operation;
	int				priority;
	struct s_group	*right;
	struct s_group	*left;

}	t_group;

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;

}	t_llist;

typedef struct s_token
{
	char			*str_val;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;

}	t_token;

typedef struct s_f_exec
{
	int		qtt_cmd;
	pid_t	pid;
	int		**pipe;
	int		n_child;
}	t_f_exec;

typedef struct s_info
{
	// t_buildin_ptr	builtins[7]; //upd 13.04.: закоментил, а то компилятор ругался 
									// A: хранятся все билтины в этом массиве указателей на функции.
	char			*res_words[7];
	char			**envp;
	t_llist			*envp_list; //функция для чистки ft_clean_envp_list
	char			**cmd_paths;
	char			**path;
	char			*str;
	int				envp_f;
	int				exit_f;
	int				status;
	t_token			*tokens;
	t_token			*token_head;
	t_llist			*envp_head;

	t_f_exec		*exec;

	t_group			*group_head;
	t_group			*group_ptr;
	t_cmds			*cmds_head;

}	t_info;

typedef int	(*t_buildin_ptr)(t_llist *, t_info *); //Д:не понимаю что это такое.
													// А:это указатель на функцию, которая принимает в себя два параметра типа t_llist* и t_info*,
													// а возвращает значение типа int.
													// Эта штука нужна для builin, которые ты пишешь.
													// см. комментарий выше... 

/* envp.c */
char		*ft_strjoin_three(char *s1, char *s2, char *s3);
void		ft_array_envp(t_info *data);
int			ft_envp2(char *envp, char **key, char **value, int j);
void		ft_envp(t_info *data);
void		ft_transfer(int argc, char **argv, char **envp, t_info *data);

/* llist.c */
t_llist		*ft_lstnew(void *key, void *value);
void		ft_lstadd_front(t_llist **lst, t_llist *new);
t_llist		*ft_lstlast(t_llist *lst);
void		ft_lstadd_back(t_llist **lst, t_llist *new);

/* ft_readline.c */
void		ft_readline(t_info *data, char *prompt, int print_exit);

/* exit.c */
int			ft_cleaning_str(char *str);
int			ft_cleaning_array(char **arr);
void		ft_clean_envp_list(t_info *data);
void		ft_clean_struct(t_info *data);
void		ft_error_exit(t_info *data, int i);

/* minishell.c */
// int			ft_lexer(t_info *data);
void		ft_cleanup(t_info *data);

/* lexer.c */
void		ft_set_flags(int *single_q, int *double_q, char *str, int k);
int			ft_get_tokens(char *str, t_info *data);
void		ft_set_tokens_type(t_info *data);

/* lexer_utils.c */
t_token		*ft_token_lstnew(char *value);
int			ft_token_lstsize(t_token *head);
t_token		*ft_token_lstlast(t_token *head);
void		ft_token_lstadd_front(t_token **head, t_token *new);
void		ft_token_lstadd_back(t_token **head, t_token *new);

/* lexer_utils_2.c */
void		ft_token_lstdelone(t_token *lst);
void		ft_token_lstclear(t_token **head);
void		ft_token_lstadd_prev(t_token *head, t_token *new);
void		ft_token_lstadd_next(t_token *head, t_token *new);
void		ft_token_lstmerge_next(t_token *node);

/* lexer_env_var.c */
// int			ft_search(const char *str, int c);
void		ft_expand(t_info *data);

/* ft_symsplit.c */
size_t		ft_search(char *s, char c);
int			ft_check_quotes(char *str, int index);
void		ft_symsplit(t_info *data);

/* parser.c */
int			ft_get_cmds(t_info *data);

/* ft_check_redir_insource.c */
int			ft_check_redir_insource(t_info *data);

/* ft_check_redir_in.c */
int			ft_check_redir_in(t_info *data);

/* ft_check_redir_out.c */
int			ft_check_redir_out(t_info *data);

/* ft_check_redir_append.c */
int			ft_check_redir_append(t_info *data);

/* ft_check_words.c */
int			ft_check_cmd_path(t_info *data);
int			ft_check_cmd_argv(t_info *data);

/* parser_cmd_utils.c */
t_cmds		*ft_cmd_lstnew(void);
t_cmds		*ft_cmd_lstlast(t_cmds *head);
void		ft_cmd_lstadd_front(t_cmds **head, t_cmds *new);
void		ft_cmd_lstadd_back(t_cmds **head, t_cmds *new);
void		ft_cmd_lstclear(t_cmds **head);

/* parser_group_utils.c */
t_group		*ft_group_lstnew(void);
t_group		*ft_group_lstlast(t_group *head);
void		ft_group_lstadd_front(t_group **head, t_group *new);
void		ft_group_lstadd_back(t_group **head, t_group *new);
void		ft_group_lstclear(t_group **head);

/* executor */
int			ft_executor(t_info *data);

/* ft_perror.c */
void		ft_perror_token(char *token_name);
void		ft_perror_eof(void);
void		ft_perror_file(t_info *data, char *infile);
void		ft_perror_symbols(t_info *data, char *symbol);
void		ft_perror_cmd(t_info *data, char *cmd);

/* checkers.c */
void		ft_check_lexer(t_info *data);
void		ft_checker(t_info *data);

#endif
