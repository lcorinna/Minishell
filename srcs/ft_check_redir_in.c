/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/22 23:41:10 by merlich          ###   ########.fr       */
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
			return (ft_perror_token(data, "newline"));
		}
		else
		{
			infile = data->token_head->str_val;
			if (data->cmds_head->infile != 0)
				close(data->cmds_head->infile);
			if (ft_strchr(infile, '*'))
				infile = ft_do_wildcard(data, infile);
			printf("infile = %s\n", infile);
			data->cmds_head->infile = open(infile, O_RDONLY);
			// printf("%d\n", data->cmds_head->infile); 
			if (data->cmds_head->infile < 0)
			{
				return (ft_perror_file(data, infile));
			}
		}
		data->token_head = data->token_head->next;
	}
	return (0);
}
