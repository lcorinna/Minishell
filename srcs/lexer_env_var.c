/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:11:40 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 16:27:59 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_interpret(t_info *data, t_token *token)
{
	char	*str;
	char	*sub_str;
	t_llist	*envp;

	str = token->str_val + ft_search_excl(token->str_val);
	sub_str = NULL;
	envp = data->envp_list;
	while (str[0] != '\0')
	{
		if (str[1] == '?')
		{
			ft_replace_2(data);
			str = token->str_val + ft_search_excl(token->str_val);
		}
		else if (str[1] == '_' || ft_isalnum(str[1]))
		{
			sub_str = ft_substr(str + 1, 0, ft_find_ind_el(str + 1));
			envp = data->envp_list;
			while (envp && ft_strncmp(sub_str, envp->key, ft_strlen(sub_str)))
				envp = envp->next;
			ft_replace(data);
			str = token->str_val + ft_search_excl(token->str_val);
			free(sub_str);
		}
	}
}

void	ft_expand(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_interpret(data, data->token_head);
		data->token_head = data->token_head->next;
	}
}
