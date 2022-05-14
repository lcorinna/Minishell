/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:06:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/14 00:09:08 by merlich          ###   ########.fr       */
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
			printf("%s\b\b: syntax error near unexpected token `newline'\n", SHELL);
			data->status = 258;
			return (data->status);
		}
		else
		{
			outfile = data->token_head->str_val;
			data->group_head->cmds_head->outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 000777);
			// printf("%d\n", data->group_head->cmds_head->outfile);
			if (data->group_head->cmds_head->outfile < 0)
			{
				ft_print_error(data, outfile);
				return (data->status);
			}
		}
	}
	return (0);
}