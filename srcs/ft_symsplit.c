/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:32:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/03 22:07:21 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_index(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(SYMBOLS, str[i]))
		i++;
	if (i == ft_strlen(str))
		i = -1;
	return (i);
}

static void	ft_set_flags(int *single_q, int *double_q, char *str, int k)
{
	if (k == 0)
	{
		if (str[k] == '\'')
			*single_q += 1;
		else if (str[k] == '\"')
			*double_q += 1;
	}
	else if (k > 0)
	{
		if (str[k] == '\'' && str[k - 1] != '\\' && !(*double_q % 2))
			*single_q += 1;
		else if (str[k] == '\"' && str[k - 1] != '\\' && !(*single_q % 2))
			*double_q += 1;
	}
}

static int	ft_check_quotes(char *str, int index)
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
	if ((single_q % 2) || (double_q % 2))
		res = 1;
	return (res);
}

static void	ft_strparse(t_info *data)
{
	int		i;
	char	*str;
	
	str = data->token_head->str_val;
	i = ft_find_index(str);
	while (i != -1)
	{
		if (!ft_check_quotes(str, i))
		{
			
			return ;
		}
		else
			i = ft_find_index(str + i + 1);
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
}
