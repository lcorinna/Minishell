/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_insource.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:40:27 by merlich           #+#    #+#             */
/*   Updated: 2022/05/18 23:57:25 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_fill_here_doc(t_info *data, char *limiter)
{
	int		fd;
	char	*buff;
	char	*tmp;

	buff = NULL;
	tmp = NULL;
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 000777);
	if (fd < 0)
	{
		ft_perror_file(data, HEREDOC);
		return ;
	}
	tmp = readline("> ");
	while (tmp && ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1))
	{
		buff = ft_strjoin(tmp, "\n\0");
		free(tmp);
		write(fd, buff, ft_strlen(buff));
		free(buff);
		tmp = readline("> ");
	}
	free(tmp);
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
			ft_perror_token("newline");
			data->status = TOKEN_ERROR;
			return (data->status);
		}
		else
		{
			limiter = data->token_head->str_val;
			ft_fill_here_doc(data, limiter);
			if (data->cmds_head->infile != 0)
				close(data->cmds_head->infile);
			data->cmds_head->infile = open(HEREDOC, O_RDONLY);
			if (data->cmds_head->infile < 0)
			{
				ft_perror_file(data, HEREDOC);
				return (data->status);
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
