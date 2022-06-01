/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:03 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 21:39:34 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_ind(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	return (i);
}

int	ft_excl_search(char *s)
{
	int		i;

	i = 0;
	if (s)
	{
		i = ft_search(s, '$');
		while (s[i] != '\0' && (ft_check_quotes(s, i) == 1 || \
			(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalnum(s[i + 1]))))
		i += ft_search(s + i + 1, '$') + 1;
	}
	return (i);
}

static char	*ft_handle_condition(t_llist *envp, char *s1, char *s2, char *s3)
{
	char	*res;

	res = NULL;
	if (envp)
	{
		s2 = ft_strjoin(s1, envp->value);
		res = ft_strjoin(s2, s3);
		free(s2);
	}
	else
		res = ft_strjoin(s1, s3);
	return (res);
}

void	ft_replace(t_llist *envp, char **token_str)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = *token_str;
	ind = ft_excl_search(s0);
	s1 = ft_substr(s0, 0, ind);
	s2 = NULL;
	s3 = ft_substr(s0, ind + 1 + ft_find_ind(s0 + ind + 1), ft_strlen(s0));
	*token_str = ft_handle_condition(envp, s1, s2, s3);
	if (*token_str[0] == '\0')
	{
		free(*token_str);
		*token_str = ft_strdup("\t");
	}
	free(s0);
	free(s1);
	free(s3);
}

void	ft_replace_2(t_info *data, char **token_str)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = *token_str;
	ind = ft_excl_search(s0);
	s1 = ft_substr(s0, 0, ind);
	s3 = ft_itoa(data->status);
	s2 = ft_strjoin(s1, s3);
	free(s1);
	free(s3);
	s3 = ft_substr(s0, ind + 2, ft_strlen(s0 + ind + 2));
	free(s0);
	*token_str = ft_strjoin(s2, s3);
	free(s2);
	free(s3);
}
