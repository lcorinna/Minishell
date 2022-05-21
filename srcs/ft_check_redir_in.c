/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/22 00:01:52 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_do_wildcard(t_info *data)
{
	DIR				*curr_dir;
	struct dirent	*s_dir;

	curr_dir = opendir("./");
	while (s_dir = readdir(curr_dir))
	{
		printf("%s\n", s_dir->d_name);	
	}
	closedir(curr_dir);
}

int	ft_check_redir_in(t_info *data)
{
	char	*infile;

	infile = NULL;
	if (data->token_head->type == REDIR_IN)
	{
		data->token_head = data->token_head->next;
		if (!data->token_head)
		{
			return (ft_perror_token(data, "newline"));
		}
		else
		{
			infile = data->token_head->str_val;
			if (ft_strchr(infile, '*'))
				ft_do_wildcard(data);
			if (data->cmds_head->infile != 0)
				close(data->cmds_head->infile);
			data->cmds_head->infile = open(infile, O_RDONLY);
			if (data->cmds_head->infile < 0)
			{
				return (ft_perror_file(data, infile));
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
