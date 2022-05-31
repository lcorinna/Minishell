/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:31:23 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 20:13:43 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_perror_token_symbol(t_info *data, char *token_name)
{
	char	*s;
	char	*tmp;
	char	*first;

	tmp = ft_strjoin(SHELL, "\b\b: syntax error near unexpected token `");
	first = ft_substr(token_name, 0, 1);
	s = ft_strjoin_three(tmp, first, "'\n");
	free(tmp);
	free(first);
	ft_putstr_fd(s, 2);
	free(s);
	data->status = TOKEN_ERROR;
	return (data->status);
}

int	ft_check_tokens(t_info *data)
{
	t_token	*t;
	t_token	*t1;

	t = 0;
	t1 = 0;
	data->token_head = data->tokens;
	if (data->token_head)
	{
		while (data->token_head->next)
		{
			t = data->token_head;
			t1 = data->token_head->next;
			if (t->type != WORD && t1->type != WORD)
			{
				return (ft_perror_token_symbol(data, t1->str_val));
			}
			data->token_head = data->token_head->next;
		}
	}
	return (0);
}
