/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_insource.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:40:27 by merlich           #+#    #+#             */
/*   Updated: 2022/05/15 22:41:36 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(t_info *data, char *infile)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(SHELL, "\b\b: ");
	s2 = ft_strjoin(s1, infile);
	perror(s2);
	free(s1);
	free(s2);
	data->status = errno;
}

static void	ft_fill_here_doc(t_info *data, char *limiter)
{
	int		fd;
	char	*buff;

	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 000777);
	if (fd < 0)
	{
		ft_print_error(data, HEREDOC);
		return ;
	}
	write(1, "> ", 2);
	buff = get_next_line(0);
	while (buff && ft_strncmp(buff, limiter, ft_strlen(limiter))) // Не работает так, как положено
	{
		write(1, "> ", 2);
		write(fd, buff, ft_strlen(buff));
		free(buff);
		buff = get_next_line(0);
	}
	free(buff);
	close(fd);
}

int	ft_check_redir_insource(t_info *data)
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
			return (data->status);
		}
		else
		{
			limiter = data->token_head->str_val;
			// printf("res = %d\n", ft_strncmp("1", "123", 2));
			ft_fill_here_doc(data, limiter);
			if (data->cmds_head->infile != 0)
				close(data->cmds_head->infile);
			data->cmds_head->infile = open(HEREDOC, O_RDONLY);
			// printf("%d\n", data->group_head->cmds_head->infile);
			if (data->cmds_head->infile < 0)
			{
				ft_print_error(data, HEREDOC);
				return (data->status);
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}

