/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:05:32 by merlich           #+#    #+#             */
/*   Updated: 2022/05/08 22:25:05 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_flags(int *single_q, int *double_q, char *str, int k)
{
	if (str[k] == '\'' && !(*double_q) && !(*single_q))
		*single_q += 1;
	else if (str[k] == '\"' && !(*single_q) && !(*double_q))
		*double_q += 1;
	else if (str[k] == '\'' && !(*double_q) && *single_q)
		*single_q -= 1;
	else if (str[k] == '\"' && !(*single_q) && *double_q)
		*double_q -= 1;
}

static int	ft_check_unclosed_quotes(t_info *data, char *str, int *i)
{
	int		single_q;
	int		double_q;

	single_q = 0;
	double_q = 0;
	ft_set_flags(&single_q, &double_q, str, *i);
	(*i)++;
	while (str[*i] && (single_q || double_q))
	{
		ft_set_flags(&single_q, &double_q, str, *i);
		(*i)++;
	}
	if (single_q || double_q)
	{
		ft_token_lstclear(&data->tokens);
		write(1, "QUOTES ERROR\n", 13);
		return (LEXER_ERROR);
	}
	return (0);
}

int	ft_get_tokens(char *str, t_info *data)
{
	int		i;
	char	*sub_str;

	sub_str = NULL;
	while (str[0])
	{
		i = 0;
		while (str[i] && !ft_strchr(SPACES, str[i]))
		{
			if (ft_check_unclosed_quotes(data, str, &i))
				return (LEXER_ERROR);
		}
		if (i)
		{
			sub_str = ft_substr(str, 0, i);
			ft_token_lstadd_back(&data->tokens, ft_token_lstnew(sub_str));
			// ft_token_lstadd_back(&data->tokens, ft_token_lstnew(" "));
		}
		else if (str[i] && i == 0)
			i++;
		str = str + i;
	}
	// ft_token_dellast(&data->tokens);
	return (0);
}

static int	ft_get_type(char *str)
{
	if (!ft_strncmp(str, ">", ft_strlen(str)))
		return (REDIR_OUT);
	else if (!ft_strncmp(str, "<", ft_strlen(str)))
		return (REDIR_IN);
	else if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (PIPE);
	else if (!ft_strncmp(str, "(", ft_strlen(str)))
		return (PARN_L);
	else if (!ft_strncmp(str, ")", ft_strlen(str)))
		return (PARN_R);
	else if (!ft_strncmp(str, ">>", ft_strlen(str)))
		return (REDIR_APPEND);
	else if (!ft_strncmp(str, "<<", ft_strlen(str)))
		return (REDIR_INSOURCE);
	else if (!ft_strncmp(str, "&&", ft_strlen(str)))
		return (IF_AND);
	else if (!ft_strncmp(str, "||", ft_strlen(str)))
		return (IF_OR);
	else
		return (WORD);
}

void	ft_set_tokens_type(t_info *data)
{
	t_token *head;

	head = data->tokens;
	while (head)
	{
		head->type = ft_get_type(head->str_val);
		head = head->next;
	}
}
