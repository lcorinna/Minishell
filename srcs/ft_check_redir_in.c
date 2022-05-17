/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/17 17:03:28 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redir_in(t_info *data)
{
	char	*infile;

	infile = NULL;
	if (data->token_head->type == REDIR_IN)
	{
		data->token_head = data->token_head->next;
		if (!data->token_head)
		{
			ft_perror_token("newline");
			data->status = 258;
			return (data->status);
		}
		else
		{
			infile = data->token_head->str_val;
			if (data->cmds_head->infile != 0)
				close(data->cmds_head->infile);
			data->cmds_head->infile = open(infile, O_RDONLY);
			if (data->cmds_head->infile < 0)
			{
				ft_perror_file(data, infile);
				return (data->status);
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
