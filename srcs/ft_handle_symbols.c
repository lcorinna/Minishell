/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_symbols.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:32:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/27 23:01:07 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_index(char *str, size_t	len)
{
	size_t	i;

	i = 0;
	while ((i < len) && !ft_strchr(SYMBOLS, str[i]))
		i++;
	return (i);
}

static void	ft_symsplit(t_info *data, char *str, size_t ind, size_t len)
{
	char	*prev;
	char	*next;

	next = NULL;
	prev = NULL;
	if (ind < len)
	{
		if (ind < len - 1)
			next = ft_substr(str, ind + 1, len);
		ft_token_lstadd_next(data->token_head, ft_token_lstnew(next));
		data->token_head->str_val = ft_substr(str, ind, 1);
		if (ind)
			prev = ft_substr(str, 0, ind);
		ft_token_lstadd_prev(data->token_head, ft_token_lstnew(prev));
		free(str);
		str = NULL;
	}
}

static void	ft_strparse(t_info *data)
{
	char	*str;
	size_t	len;
	size_t	ind;

	str = data->token_head->str_val;
	len = ft_strlen(str);
	ind = ft_find_index(str, len);
	if (len > 1)
	{
		while (ind < len && ft_check_quotes(str, ind))
		{
			ind += ft_find_index(str + ind + 1, len - ind - 1) + 1;
		}
		ft_symsplit(data, str, ind, len);
	}
}

static void	ft_merge(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head && data->token_head->next)
	{
		if (data->token_head->type != WORD \
			&& data->token_head->type != PARN_L \
			&& data->token_head->type != PARN_R \
			&& data->token_head->type == data->token_head->next->type)
			ft_token_lstmerge_next(data->token_head);
		data->token_head = data->token_head->next;
	}
}

void	ft_handle_symbols(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_strparse(data);
		data->token_head = data->token_head->next;
	}
	if (data->tokens)
	{
		while (data->tokens->prev)
		data->tokens = data->tokens->prev;
	}
	ft_set_tokens_type(data);
	ft_merge(data);
}
