/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/26 18:49:06 by merlich          ###   ########.fr       */
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
# define TOKEN_ERROR	258
# define CMD_NOT_FOUND	127
# define AMBIG_REDIR	1
# define UNDEFINED		-1
# define WORD			1
# define REDIR_OUT		4
# define REDIR_IN		5
# define REDIR_APPEND	6
# define REDIR_INSOURCE	7
# define PIPE			8
# define AND			13
# define IF_AND			9 //&&
# define IF_OR			10 //||
# define PARN_L			11
# define PARN_R			12
# define DUP			81

typedef struct s_cmds
{
	int				infile;
	int				outfile;
	char			*cmd_path;
	char			*cmd_str;
	char			**cmd_argv;
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
	char			*res_words[8];
	char			**envp;
	t_llist			*envp_list; //функция для чистки ft_clean_envp_list
	char			*str;
	int				envp_f;
	int				exit_f;
	int				status;
	int				priority;
	t_token			*tokens;
	t_group			*group_head;
	t_group			*root;
	t_list			*dir_files;

	t_token			*token_head;
	t_llist			*envp_head;
	t_group			*group_ptr;
	t_cmds			*cmds_head;
	t_list			*dir_head;
	t_f_exec		*exec;

}	t_info;

/* srcs/builtins/builtins_utils.c */
int			ft_memcmp_l(const void *s1, const void *s2, size_t n);
int			ft_only_parent_need(char **arr);
void		ft_builtins_command(t_info *data, char **arr);

/* srcs/builtins/echo.c */
void		ft_echo(char **cmd_argv);

/* srcs/builtins/cd.c */

/* srcs/builtins/pwd.c */
void		ft_pwd(char **arr);

/* srcs/builtins/export.c */

/* srcs/builtins/unset.c */

/* srcs/builtins/env.c */
void		ft_env(t_info *data);

/* srcs/builtins/exit.c */
void		ft_exit(char **arr);
int			ft_is_number(char *str);

/* srcs/envp.c */
char		*ft_strjoin_three(char *s1, char *s2, char *s3);
void		ft_array_envp(t_info *data);
int			ft_envp2(char *envp, char **key, char **value, int j);
void		ft_envp(t_info *data);
void		ft_transfer(int argc, char **argv, char **envp, t_info *data);

/* srcs/llist.c */
t_llist		*ft_llstnew(void *key, void *value);
void		ft_llstadd_front(t_llist **lst, t_llist *new);
t_llist		*ft_llstlast(t_llist *lst);
void		ft_llstadd_back(t_llist **lst, t_llist *new);

/* srcs/ft_readline.c */
void		ft_readline(t_info *data, char *prompt, int print_exit);

/* srcs/exit.c */
int			ft_cleaning_str(char *str);
int			ft_cleaning_array(char **arr);
void		ft_clean_envp_list(t_info *data);
void		ft_clean_struct(t_info *data);
void		ft_error_exit(t_info *data, int i);

/* srcs/minishell.c */
// int			ft_lexer(t_info *data);
void		ft_cleanup(t_info *data);

/* srcs/lexer.c */
void		ft_set_flags(int *single_q, int *double_q, char *str, int k);
int			ft_get_tokens(char *str, t_info *data);
void		ft_set_tokens_type(t_info *data);

/* srcs/lexer_utils.c */
t_token		*ft_token_lstnew(char *value);
int			ft_token_lstsize(t_token *head);
t_token		*ft_token_lstlast(t_token *head);
void		ft_token_lstadd_front(t_token **head, t_token *new);
void		ft_token_lstadd_back(t_token **head, t_token *new);

/* srcs/lexer_utils_2.c */
void		ft_token_lstdelone(t_token *lst);
void		ft_token_lstclear(t_token **head);
void		ft_token_lstadd_prev(t_token *head, t_token *new);
void		ft_token_lstadd_next(t_token *head, t_token *new);
void		ft_token_lstmerge_next(t_token *node);

/* srcs/lexer_env_var.c */
void		ft_expand(t_info *data);

/* srcs/ft_handle_symbols.c */
size_t		ft_search(char *s, char c);
int			ft_check_quotes(char *str, int index);
void		ft_handle_symbols(t_info *data);

/* srcs/parser.c */
int			ft_get_logic_group(t_info *data);

/* srcs/ft_check_redir_insource.c */
int			ft_check_redir_insource(t_info *data);

/* srcs/ft_check_redir_in.c */
int			ft_check_redir_in(t_info *data);

/* srcs/ft_check_redir_out.c */
int			ft_check_redir_out(t_info *data);

/* srcs/ft_check_redir_append.c */
int			ft_check_redir_append(t_info *data);

/* srcs/ft_check_words.c */
int			ft_check_cmd_path(t_info *data);
int			ft_check_cmd_str(t_info *data);

/* srcs/parser_cmd_utils.c */
t_cmds		*ft_cmd_lstnew(void);
t_cmds		*ft_cmd_lstlast(t_cmds *head);
void		ft_cmd_lstadd_front(t_cmds **head, t_cmds *new);
void		ft_cmd_lstadd_back(t_cmds **head, t_cmds *new);
void		ft_cmd_lstclear(t_cmds **head);

/* srcs/parser_group_utils.c */
t_group		*ft_group_lstnew(void);
t_group		*ft_group_lstlast(t_group *head);
void		ft_group_lstadd_front(t_group **head, t_group *new);
void		ft_group_lstadd_back(t_group **head, t_group *new);
void		ft_group_lstclear(t_group **head);

/* srcs/bin_tree.c */
t_group		*ft_group_logic_last(t_group *last);
void		ft_build_bin_tree(t_info *data, t_group *last);
void		ft_free_bin_tree(t_group **root);

/* srcs/executor.c */
int			ft_executor(t_info *data);

/* srcs/executor_one_cmd.c */
void		ft_pipe_one_cmd(t_info *data);
int			ft_exec_one_cmd(t_info	*data);
void		ft_perror_exit_child(char *str, int error);
int			ft_memcmp_l(const void *s1, const void *s2, size_t n);

/* srcs/executor_many_cmd.c */
int			ft_exec_many_cmd(t_info *data);
void		ft_first_entry(t_info *data, t_cmds	*tmp);
void		ft_last_entry(t_info *data, t_cmds	*tmp);
void		ft_routine(t_info *data, t_cmds	*tmp);
int			ft_pipe_many_cmd(t_info	*data);

/* srcs/executor_utils */
void		ft_free_exec(t_info *data);
int			ft_clean_array_int(int **pipe, int qtt_cmd);
void		ft_close_all_pipes(t_info *data);
void		ft_pipe_closure(t_info *data);

/* srcs/ft_perror.c */
int			ft_perror_token(t_info *data, char *token_name);
int			ft_perror_eof(t_info *data);
int			ft_perror_file(t_info *data, char *infile);
int			ft_perror_symbols(t_info *data, char *symbol);
int			ft_perror_cmd(t_info *data, char *cmd);

/* srcs/checkers.c */
void		ft_check_lexer(t_info *data);
void		ft_checker_parser(t_info *data);
void		ft_check_bin_tree(t_group *root);

/* srcs/wildcards.c */
int			ft_perror_wcds(t_info *data, char *file);
char		*ft_do_wildcards_file(t_info *data, char *str);
char		*ft_do_wildcards_argv(t_info *data, char *str);

#endif
