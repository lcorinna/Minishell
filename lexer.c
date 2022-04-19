/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:05:32 by merlich           #+#    #+#             */
/*   Updated: 2022/04/19 23:24:40 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_tokens(char *str, t_info *data)
{
	int		i;
	char	*sub_str;

	sub_str = NULL;
	while (str[0])
	{
		i = 0;
		while (str[i] && !ft_strchr(SPACES, str[i]))
			i++;
		if (i)
		{
			sub_str = ft_substr(str, 0, i);
			ft_token_lstadd_back(&data->tokens, ft_token_lstnew(sub_str));
			ft_token_lstadd_back(&data->tokens, ft_token_lstnew(" "));
		}
		else if (str[i] && i == 0)
			i++;
		else
			break ;
		str = str + i;
	}
	ft_token_dellast(&data->tokens);
	return (0);
}

static int	ft_get_type(char *str)
{
	if (!ft_strncmp(str, "\'", ft_strlen(str)))
		return (FIELD);
	else if (!ft_strncmp(str, "\"", ft_strlen(str)))
		return (EXP_FIELD);
	else if (!ft_strncmp(str, ">", ft_strlen(str)))
		return (REDIR_OUT);
	else if (!ft_strncmp(str, "<", ft_strlen(str)))
		return (REDIR_IN);
	else if (!ft_strncmp(str, ">>", ft_strlen(str)))
		return (REDIR_APPEND);
	else if (!ft_strncmp(str, "<<", ft_strlen(str)))
		return (REDIR_INSOURCE);
	else if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (PIPE);
	else if (!ft_strncmp(str, "&&", ft_strlen(str)))
		return (IF_AND);
	else if (!ft_strncmp(str, "||", ft_strlen(str)))
		return (IF_OR);
	else if (!ft_strncmp(str, "(", ft_strlen(str)))
		return (PARN_L);
	else if (!ft_strncmp(str, ")", ft_strlen(str)))
		return (PARN_R);
	else if (!ft_strncmp(str, " ", ft_strlen(str)))
		return (IS_SPACE);
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

int main(void)
{
	t_info	data;
	t_token *head;

	char *str = "cat          >			   'file' | cat< file";
	data = (t_info){};	
	ft_get_tokens(str, &data);
	ft_set_tokens_type(&data);
	head = data.tokens;
	while (head)
	{
		printf("%s == ", head->str_val);
		printf("%d\n", head->type);
		head = head->next;
	}
}