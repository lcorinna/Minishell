/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/04/28 00:05:13 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '_' || ft_isalnum(str[i]))
		i++;
	return (i);
}

static void	ft_interpret(t_info *data, char *str)
{
	char	*sub_str;
	t_llist	*envp_head;

	sub_str = NULL;
	while (*str)
	{
		str = ft_strchr(str, '$');
		if (!str)
			break ;
		if (str && (str[1] == '_' || ft_isalpha_big(str[1])))
		{
			sub_str = ft_substr(str + 1, 0, ft_find_index(str + 1));
			printf("ENV = %s\n", sub_str);
			envp_head = data->envp_list;
			while (envp_head)
			{
				if (!ft_strncmp(sub_str, envp_head->key, ft_strlen(sub_str) + ft_strlen(envp_head->key)))
				{
					// ft_replace(token_head, envp_head->value);
					break ;
				}
				envp_head = envp_head->next;
			}
			free(sub_str);
		}
		str = str + 1;
	}
}

void	ft_expand(t_info *data)
{
	t_token *token_head;

	token_head = data->tokens;
	while (token_head)
	{
		ft_interpret(data, token_head->str_val);
		token_head = token_head->next;   
	}
}

// int	main(void)
// {
// 	char	*s = "$USER>*()";

// 	s = ft_substr(s + 1, 0, ft_find_index(s + 1));
	
// 	printf("ENV = %s\n", s);
// 	printf("index = %d\n", ft_find_index(s));
// 	return (0);
// }
