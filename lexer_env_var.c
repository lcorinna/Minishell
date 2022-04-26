/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/04/26 21:47:26 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_info *data)
{
	char	*str;
	t_token *head;

	str = NULL;
	head = data->tokens;
	while (head)
	{
		str = ft_strchr(head->str_val, '$');
		if (str)
		{
			// printf("%s\n", str);
			while (data->envp_list)
			{
				if (!ft_strncmp(str, data->envp_list->key, ft_strlen(str)))
				{
					
					break ;
				}
				data->envp_list = data->envp_list->next;
			}
			// ft_replace();
		}
		head = head->next;   
	}
}
