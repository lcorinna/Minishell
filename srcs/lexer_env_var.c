/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/05/01 22:57:06 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	return (i);
}

int	ft_search(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char) str[i] == (unsigned char) c)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_replace(t_info *data)
{
	int		ind;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = data->token_head->str_val;
	printf("---------\ns0 = %s\n---------\n", s0);	
	ind = ft_search(s0, '$');
	s1 = ft_substr(s0, 0, ind);
	s2 = NULL;
	s3 = ft_substr(s0, ind + 1 + ft_find_index(s0 + ind + 1), ft_strlen(s0));
	free(data->token_head->str_val);  // free(s0); -- имеет такую же силу
	data->token_head->str_val = NULL;
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

static void	ft_interpret(t_info *data)
{
	char 	*str;
	char	*sub_str;

	str = ft_strchr(data->token_head->str_val, '$');
	sub_str = NULL;
	while (str)
	{
		if (str[1] == '_' || ft_isalpha_big(str[1]))
		{
			sub_str = ft_substr(str + 1, 0, ft_find_index(str + 1));
			data->envp_head = data->envp_list;
			while (data->envp_head && ft_strncmp(sub_str, data->envp_head->key, ft_strlen(sub_str) + ft_strlen(data->envp_head->key)))
				data->envp_head = data->envp_head->next;
			ft_replace(data);
			str = ft_strchr(data->token_head->str_val, '$');
			free(sub_str);
		}
		else
			str = ft_strchr(str + 1, '$');
	}
}

void	ft_expand(t_info *data)
{
	t_token *tmp;

	tmp = NULL;
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_interpret(data);
		data->token_head = data->token_head->next;   
	}
	data->token_head = data->tokens;
}

// int	main(void)
// {
// 	char	*s = "$USER>*()";

// 	s = ft_substr(s + 1, 0, ft_find_index(s + 1));
	
// 	printf("ENV = %s\n", s);
// 	printf("index = %d\n", ft_find_index(s));

	
	
// 	return (0);
// }
