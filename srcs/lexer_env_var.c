/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 21:48:56 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_interpret(t_info *data)
{
	char	*str;
	char	*sub_str;
	char	**token_str;
	t_llist	*envp;

	token_str = &data->token_head->str_val;
	envp = data->envp_list;
	str = *token_str + ft_excl_search(*token_str);
	sub_str = NULL;
	while (str[0] != '\0')
	{
		if (str[1] == '?')
		{
			ft_replace_2(data, token_str);
			str = *token_str + ft_excl_search(*token_str);
		}
		else if (str[1] == '_' || ft_isalnum(str[1]))
		{
			sub_str = ft_substr(str + 1, 0, ft_find_ind(str + 1));
			envp = data->envp_list;
			while (envp && ft_strncmp(sub_str, envp->key, ft_strlen(sub_str)))
				envp = envp->next;
			ft_replace(envp, token_str);
			str = *token_str + ft_excl_search(*token_str);
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
