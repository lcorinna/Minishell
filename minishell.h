/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:17:58 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/13 19:15:56 by lcorinna         ###   ########.fr       */
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

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;

}	t_llist;

typedef struct s_info
{
	// t_buildin_ptr	builtins[7]; //upd 13.04.: закоментил, а то компилятор ругался 
	char			*res_words[7];
	char			**envp;
	t_llist			envp_list;
	char			envp_t;
	char			exit_t;
	int				status;

}	t_info;

// typedef int	(*t_buildin_ptr)(t_llist *, t_info *); //Д:не понимаю что это такое. upd 13.04.: закоментил, а то компилятор ругался 

typedef	struct s_malloc
{
	/* Здесь хранятся указатели 
	на всю выделенную с помощью malloc память */
	
	/* Если malloc, сразу заносим сюда */

}	t_malloc;


#endif
