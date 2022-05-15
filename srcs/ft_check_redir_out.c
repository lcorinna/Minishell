/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/15 23:06:34 by merlich          ###   ########.fr       */
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
			printf("%s\b\b: syntax error near unexpected token `newline'\n", SHELL);
			data->status = 258;
			return (data->status);
		}
		else
		{
			outfile = data->token_head->str_val;
			if (data->cmds_head->outfile != 1)
				close(data->cmds_head->outfile);
			data->cmds_head->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 000777);
			// printf("%d\n", data->cmds_head->outfile);
			if (data->cmds_head->outfile < 0)
			{
				ft_print_error(data, outfile);
				return (data->status);
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
