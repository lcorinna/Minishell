/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 12:05:05 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	return (i);
}

// static int	ft_search(const char *str, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i] != '\0' && (unsigned char) str[i] != (unsigned char) c)
// 			i++;
// 	}
// 	return (i);
// }

static int	ft_excluding_search(char *s)
{
	int		i;

	i = ft_search(s, '$');
	while (s[i] != '\0' && (ft_check_quotes(s, i) == 1 || (s[i + 1] !=  '_' && s[i + 1] !=  '?' && !ft_isalnum(s[i + 1]))))
		i += ft_search(s + i + 1, '$') + 1;
	return (i);
}

static void	ft_replace(t_info *data)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = data->token_head->str_val;
	// printf("---------\ns0 = %s\n---------\n", s0);	
	ind = ft_excluding_search(s0);
	s1 = ft_substr(s0, 0, ind);
	s2 = NULL;
	s3 = ft_substr(s0, ind + 1 + ft_find_index(s0 + ind + 1), ft_strlen(s0));
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

static void	ft_replace_2(t_info *data)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = data->token_head->str_val;
	// printf("---------\ns0 = %s\n---------\n", s0);
	ind = ft_excluding_search(s0);
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

static void	ft_interpret(t_info *data)
{
	char	*str;
	char	*sub_str;

	str = data->token_head->str_val + ft_excluding_search(data->token_head->str_val);
	sub_str = NULL;
	while (str[0] != '\0')
	{
		if (str[1] == '?')
		{
			ft_replace_2(data);
			str = data->token_head->str_val + ft_excluding_search(data->token_head->str_val);
		}
		else if (str[1] == '_' || ft_isalnum(str[1]))
		{
			sub_str = ft_substr(str + 1, 0, ft_find_index(str + 1));
			data->envp_head = data->envp_list;
			while (data->envp_head && ft_strncmp(sub_str, data->envp_head->key, ft_strlen(sub_str) + ft_strlen(data->envp_head->key)))
				data->envp_head = data->envp_head->next;
			ft_replace(data);
			str = data->token_head->str_val + ft_excluding_search(data->token_head->str_val);
			free(sub_str);
		}
	}
}

void	ft_expand(t_info *data)
{
	t_token	*tmp;

	tmp = NULL;
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_interpret(data);
		data->token_head = data->token_head->next;
	}
}
