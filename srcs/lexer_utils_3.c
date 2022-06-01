/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:00:20 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 19:39:48 by merlich          ###   ########.fr       */
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

static char	*ft_cut_quotes(char *str, int *ind)
{
	int		j;
	char	*before;
	char	*medium;
	char	*after;
	char	*tmp;

	j = 0;
	if (str)
	{
		before = ft_substr(str, 0, *ind);
		tmp = ft_substr(str, *ind + 1, ft_strlen(str + *ind + 1));
		j = ft_search(tmp, str[*ind]);
		medium = ft_substr(tmp, 0, j);
		after = ft_substr(tmp, j + 1, ft_strlen(tmp));
		free(tmp);
		free(str);
		str = ft_strjoin_three(before, medium, after);
		free(before);
		free(medium);
		free(after);
		*ind = *ind + j - 1;
	}
	return (str);
}

static void	ft_check_and_cut(t_info *data)
{
	int		i;
	char	*s;

	i = 0;
	s = data->token_head->str_val;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			data->token_head->str_val = ft_cut_quotes(s, &i);
			s = data->token_head->str_val;
		}
		else
			i++;
	}
}

void	ft_cut_all_quotes(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_check_and_cut(data);
		data->token_head = data->token_head->next;
	}
}
