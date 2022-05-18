/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:06:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/18 23:57:25 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redir_append(t_info *data)
{
	char	*outfile;

	outfile = NULL;
	if (data->token_head->type == REDIR_APPEND)
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
			outfile = data->token_head->str_val;
			if (data->cmds_head->outfile != 1)
				close(data->cmds_head->outfile);
			data->cmds_head->outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 000777);
			// printf("%d\n", data->cmds_head->outfile);
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
