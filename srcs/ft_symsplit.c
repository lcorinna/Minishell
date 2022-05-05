/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:32:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/05 22:27:50 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_strchr(SYMBOLS, str[i]))
		i++;
	return (i);
}

static int	ft_check_quotes(char *str, int index)
{
	int		k;
	int		res;
	int		single_q;
	int		double_q;

	k = 0;
	res = 0;
	single_q = 0;
	double_q = 0;
	while (str[k] && k < index)
	{
		ft_set_flags(&single_q, &double_q, str, k);
		k++;
	}
	if (single_q || double_q)
		res = 1;
	return (res);
}

static void	ft_strparse(t_info *data)
{
	int		i;
	char	*str;
	t_token	*curr_elem;

	curr_elem = data->token_head;
	str = curr_elem->str_val;
	i = ft_find_index(str);
	while (str[i])
	{
		if (!ft_check_quotes(str, i))
		{
			ft_token_lstadd_next(curr_elem, ft_token_lstnew(ft_substr(str, i + 1, ft_strlen(str))));
			curr_elem->str_val = ft_substr(str, i, 1);
			ft_token_lstadd_prev(curr_elem, ft_token_lstnew(ft_substr(str, 0, i)));
			free(str);
			// printf("%s\n", curr_elem->str_val);
			// printf("%p\n", curr_elem);
			// printf("%s\n", data->token_head->str_val);
			// printf("%p\n", data->token_head);
			// printf("%s\n", curr_elem->next->str_val);
			// printf("%p\n", &curr_elem->next);
			// printf("%s\n", curr_elem->prev->str_val);
			// printf("%p\n", &curr_elem->prev);
			return ;
		}
		else
		{
			i += ft_find_index(str + i + 1) + 1;
		}
	}
}

void	ft_symsplit(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_strparse(data);
		data->token_head = data->token_head->next;
	}
	while (data->tokens->prev)
		data->tokens = data->tokens->prev;
}


// int	main(void)
// {
// 	t_token *head;
// 	t_token	*my_head;

// 	head = NULL;
// 	ft_token_lstadd_front(&head, ft_token_lstnew("str1"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str2"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str4"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str5"));
// 	my_head = head;
// 	while (head)
// 	{
// 		printf("%s\n", head->str_val);
// 		head = head->next;
// 	}
// 	head = my_head;
// 	// ft_token_lstadd_front(&head->next->next, ft_token_lstnew("str3"));
// 	ft_token_lstadd_next(&head->next, ft_token_lstnew("str3"));
// 	printf("--------\n");
// 	while (head)
// 	{
// 		printf("%s\n", head->str_val);
// 		head = head->next;
// 	}
// }