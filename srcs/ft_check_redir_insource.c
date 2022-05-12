/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_insource.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:40:27 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 00:04:31 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_error(t_info *data, char *msg)
{
	perror(msg);
	data->status = errno;
	exit(1); // Отправляем сигнал в main о переходе на новый виток цикла while
}

static void	ft_fill_here_doc(t_info *data, char *limiter)
{
	int		fd;
	char	*buff;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 000777);
	if (fd < 0)
		ft_print_error(data, "Error infile");
	write(1, "> ", 2);
	buff = get_next_line(0);
	while (buff && ft_strncmp(buff, limiter, ft_strlen(limiter)))
	{
		write(1, "> ", 2);
		write(fd, buff, ft_strlen(buff));
		free(buff);
		buff = get_next_line(0);
	}
	free(buff);
	close(fd);
}

// 	ft_readline(data, "> ", 0);
// 	if (!data->free_me.str) //обработка сигнала "control + d"
// 	{
// 		printf("\x1b[F> %s\b\b: syntax error: unexpected end of file\n", SHELL);
// 		return (LEXER_ERROR);
// 	}

// ft_readline(&data, "minishell$ ", 1);
// 		if (!data.free_me.str) //обработка сигнала "control + d"
// 		{
// 			break ;
// 		}

void	ft_check_redir_insource(t_info *data)
{
	char	*limiter;

	limiter = NULL;
	if (data->token_head->type == REDIR_INSOURCE)
	{
		data->token_head = data->token_head->next;
		if (!data->token_head)
		{
			printf("%s\b\b: syntax error near unexpected token `newline'\n", SHELL);
			data->status = 258;
			exit(258);  // Отправляем сигнал в main о переходе на новый виток цикла while
		}
		else
		{
			limiter = data->token_head->str_val;
			ft_fill_here_doc(data, limiter);
			data->group_head->cmds_head->infile = open(".here_doc", O_RDONLY);
			// printf("%d\n", data->group_head->cmds_head->infile);
			if (data->group_head->cmds_head->infile < 0)
				ft_print_error(data, "Error infile");
		}
	}
}

