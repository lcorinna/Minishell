/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:03 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 21:50:57 by merlich          ###   ########.fr       */
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

	i = ft_search(s, '$');
	while (s[i] != '\0' && (ft_check_quotes(s, i) == 1 || \
			(s[i + 1] != '_' && s[i + 1] != '?' && !ft_isalnum(s[i + 1]))))
		i += ft_search(s + i + 1, '$') + 1;
	return (i);
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
	free(s0);
	if (envp)
	{
		s2 = ft_strjoin(s1, envp->value);
		*token_str = ft_strjoin(s2, s3);
		free(s2);
	}
	else
	{
		*token_str = ft_strjoin(s1, s3);
		// printf("s1 = %s\n", s1);
		// printf("s3 = %s\n", s3);
		// printf("res = %s\n", *token_str);
	}
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
