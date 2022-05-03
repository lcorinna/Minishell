/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:05:32 by merlich           #+#    #+#             */
/*   Updated: 2022/05/03 22:10:10 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	ft_set_flags(int *single_q, int *double_q, char *str, int k)
// {
// 	if (k == 0)
// 	{
// 		if (str[k] == '\'')
// 			*single_q += 1;
// 		else if (str[k] == '\"')
// 			*double_q += 1;
// 	}
// 	else if (k > 0)
// 	{
// 		if (str[k] == '\'' && str[k - 1] != '\\' && !(*double_q % 2))
// 			*single_q += 1;
// 		else if (str[k] == '\"' && str[k - 1] != '\\' && !(*single_q % 2))
// 			*double_q += 1;
// 	}
// }

static void	ft_set_flags(int *flag_1, int *flag_2, char *str, int *i)
{
	if (str[*i] == '\'')
		*flag_1 += 1;
	else if (str[*i] == '\"')
		*flag_2 += 1;
	(*i)++;
}

static void	ft_unset_flags(int *flag_1, int *flag_2, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*flag_1 -= 1;
		(*i)++;
	}
	else if (str[*i] == '\"')
	{
		*flag_2 -= 1;
		(*i)++;
	}
}

static int	ft_check_quotes(t_info *data, char *str, int *i)
{
	int		flag_1;
	int		flag_2;

	flag_1 = 0;
	flag_2 = 0;
	ft_set_flags(&flag_1, &flag_2, str, i);
	while (str[*i] && (flag_1 > 0 || flag_2 > 0))
	{
		while (str[*i] && !ft_strchr(QUOTES, str[*i]))
			(*i)++;
		ft_unset_flags(&flag_1, &flag_2, str, i);
	}
	if (flag_1 > 0 || flag_2 > 0)
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
			if (ft_check_quotes(data, str, &i))
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

// static int	ft_get_type(char *str)
// {
// 	if (!ft_strncmp(str, "\'", ft_strlen(str)))
// 		return (FIELD);
// 	else if (!ft_strncmp(str, "\"", ft_strlen(str)))
// 		return (EXP_FIELD);
// 	else if (!ft_strncmp(str, ">", ft_strlen(str)))
// 		return (REDIR_OUT);
// 	else if (!ft_strncmp(str, "<", ft_strlen(str)))
// 		return (REDIR_IN);
// 	else if (!ft_strncmp(str, ">>", ft_strlen(str)))
// 		return (REDIR_APPEND);
// 	else if (!ft_strncmp(str, "<<", ft_strlen(str)))
// 		return (REDIR_INSOURCE);
// 	else if (!ft_strncmp(str, "|", ft_strlen(str)))
// 		return (PIPE);
// 	else if (!ft_strncmp(str, "&&", ft_strlen(str)))
// 		return (IF_AND);
// 	else if (!ft_strncmp(str, "||", ft_strlen(str)))
// 		return (IF_OR);
// 	else if (!ft_strncmp(str, "(", ft_strlen(str)))
// 		return (PARN_L);
// 	else if (!ft_strncmp(str, ")", ft_strlen(str)))
// 		return (PARN_R);
// 	else if (!ft_strncmp(str, " ", ft_strlen(str)))
// 		return (IS_SPACE);
// 	else
// 		return (WORD);
// }

// void	ft_set_tokens_type(t_info *data)
// {
// 	t_token *head;

// 	head = data->tokens;
// 	while (head)
// 	{
// 		head->type = ft_get_type(head->str_val);
// 		head = head->next;
// 	}
// }

// int main(void)
// {
// 	t_info	data;
// 	t_token *head;

// 	char *str = "cat          >	$9 $	$USER;	   '\"file	$ $USER1; $USER2  \"'ffff user  | $USER3 cat< file";
// 	data = (t_info){};
	
// 	ft_get_tokens(str, &data);
// 	ft_expand(&data);
// 	// ft_set_tokens_type(&data);
// 	head = data.tokens;
// 	while (head)
// 	{
// 		printf("string == %s\n", head->str_val);
// 		// printf("type == %d\n\n", head->type);
// 		head = head->next;
// 	}
// }
