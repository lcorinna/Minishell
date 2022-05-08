/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/08 23:31:39 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_groups(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		
		data->token_head = data->token_head->next;
	}
}