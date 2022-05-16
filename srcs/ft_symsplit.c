/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:32:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/16 21:52:35 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_search(char *s, char c)
{
	size_t	ind;
	size_t	len;

	ind = 0;
	len = ft_strlen(s);
	while ((ind < len) && ((unsigned char) s[ind] != (unsigned char) c))
	{
		ind++;
	}
	return (ind);
}

static int	ft_find_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_strchr(SYMBOLS, str[i]))
		i++;
	return (i);
}

int	ft_check_quotes(char *str, int index)
{
	int		k;
	int		res;
	int		single_q;
	int		double_q;

	k = 0;
	res = 0;
	single_q = 0;
	double_q = 0;
	while (str[k] && k < index)
	{
		ft_set_flags(&single_q, &double_q, str, k);
		k++;
	}
	if (single_q)
		res = 1;
	else if (double_q)
		res = 2;
	return (res);
}

static void	ft_strparse(t_info *data)
{
	int		i;
	char	*str;
	t_token	*curr_elem;

	curr_elem = data->token_head;
	str = curr_elem->str_val;
	i = ft_find_index(str);
	while (str[i])
	{
		if (!ft_check_quotes(str, i))
		{
			ft_token_lstadd_next(curr_elem, ft_token_lstnew(ft_substr(str, i + 1, ft_strlen(str))));
			curr_elem->str_val = ft_substr(str, i, 1);
			ft_token_lstadd_prev(curr_elem, ft_token_lstnew(ft_substr(str, 0, i)));
			free(str);
			str = NULL;
			return ;
		}
		else
		{
			i += ft_find_index(str + i + 1) + 1;
		}
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

void	ft_symsplit(t_info *data)
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
