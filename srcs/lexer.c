/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:01:40 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 20:54:28 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_parentheses(t_info *data)
{
	int	left;
	int	right;
	int	res;

	left = 0;
	right = 0;
	res = 0;
	data->token_head = data->tokens;
	while (data->token_head)
	{
		if (data->token_head->type == PARN_L)
			left++;
		else if (data->token_head->type == PARN_R)
			right++;
		data->token_head = data->token_head->next;
	}
	if (left == right)
		res = 0;
	else if (left < right)
		res = ft_perror_token(data, ")");
	else if (left > right)
		res = 1;
	return (res);
}

int	ft_get_tokens_from_string(t_info *data)
{
	int	parn_num;
	int	last_type;

	parn_num = 0;
	last_type = UNDEFINED;
	if (ft_get_tokens(data->str, data))
		return (data->status);
	ft_expand(data);
	ft_split_symbols(data);
	ft_set_tokens_type(data);
	if (data->tokens && ft_strchr(NOT_FIRST, data->tokens->str_val[0]))
		return (ft_perror_token(data, data->tokens->str_val));
	parn_num = ft_check_parentheses(data);
	if (parn_num == TOKEN_ERROR)
		return (data->status);
	if (data->tokens)
		last_type = ft_token_lstlast(data->tokens)->type;
	if (parn_num || (data->tokens && (last_type == PIPE || last_type == AND \
		|| last_type == IF_AND || last_type == IF_OR)))
	{
		if (!ft_readline(data, "> ", 0) || ft_get_tokens_from_string(data))
			return (data->status);
	}
	return (0);
}
