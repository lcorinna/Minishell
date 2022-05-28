/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:25:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 16:27:55 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_ind_el(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	return (i);
}

int	ft_search_excl(char *s)
{
	int		i;

	i = ft_search(s, '$');
	while (s[i] != '\0' && (ft_check_quotes(s, i) == 1 || \
			(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalnum(s[i + 1]))))
		i += ft_search(s + i + 1, '$') + 1;
	return (i);
}

void	ft_replace(t_info *data)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = data->token_head->str_val;
	ind = ft_search_excl(s0);
	s1 = ft_substr(s0, 0, ind);
	s2 = NULL;
	s3 = ft_substr(s0, ind + 1 + ft_find_ind_el(s0 + ind + 1), ft_strlen(s0));
	free(data->token_head->str_val);
	if (data->envp_head)
	{
		s2 = ft_strjoin(s1, data->envp_head->value);
		data->token_head->str_val = ft_strjoin(s2, s3);
		free(s2);
	}
	else
		data->token_head->str_val = ft_strjoin(s1, s3);
	free(s1);
	free(s3);
}

void	ft_replace_2(t_info *data)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = data->token_head->str_val;
	ind = ft_search_excl(s0);
	s1 = ft_substr(s0, 0, ind);
	s3 = ft_itoa(data->status);
	s2 = ft_strjoin(s1, s3);
	free(s1);
	free(s3);
	s3 = ft_substr(s0, ind + 2, ft_strlen(s0 + ind + 2));
	free(s0);
	data->token_head->str_val = ft_strjoin(s2, s3);
	free(s2);
	free(s3);
}
