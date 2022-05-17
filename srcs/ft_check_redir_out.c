/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/17 17:03:40 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redir_out(t_info *data)
{
	char	*outfile;

	outfile = NULL;
	if (data->token_head->type == REDIR_OUT)
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
			outfile = data->token_head->str_val;
			if (data->cmds_head->outfile != 1)
				close(data->cmds_head->outfile);
			data->cmds_head->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 000777);
			if (data->cmds_head->outfile < 0)
			{
				ft_perror_file(data, outfile);
				return (data->status);
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
