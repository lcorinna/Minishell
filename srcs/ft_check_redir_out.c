/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/24 21:25:28 by merlich          ###   ########.fr       */
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
			return (ft_perror_token(data, "newline"));
		else
		{
			outfile = ft_strdup(data->token_head->str_val);
			if (data->cmds_head->outfile != 1)
				close(data->cmds_head->outfile);
			if (ft_strchr(outfile, '*'))
				outfile = ft_do_wildcards_file(data, outfile);
			if (!outfile)
				return (ft_perror_wcds(data, data->token_head->str_val));
			data->cmds_head->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (data->cmds_head->outfile < 0)
				return (ft_perror_file(data, outfile));
			free(outfile);
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
