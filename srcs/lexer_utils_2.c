/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:51:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/11 21:26:07 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_last_but_one(t_token *head)
{
	if (head != NULL)
	{
		while (head->next->next != NULL)
		{
			head = head->next;
		}
	}
	return (head);
}

void	ft_token_dellast(t_token **head)
{
	t_token	*last;
	t_token	*last_but_one;

	last_but_one = ft_token_last_but_one(*head);
	last = ft_token_lstlast(*head);
	last_but_one->next = NULL;
	if (ft_strncmp(last->str_val, " ", ft_strlen(last->str_val)))
	{
		free(last->str_val);
		last->str_val = NULL;
	}
	free(last);
	last = NULL;
}

void	ft_token_lstclear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		if (ft_strncmp(tmp->str_val, " ", ft_strlen(tmp->str_val)))
		{
			free(tmp->str_val);
			tmp->str_val = NULL;
		}	
		free(tmp);
		tmp = NULL;
	}
}

void	ft_token_lstadd_prev(t_token *head, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (head)
	{
		tmp = (head)->prev;
		if (NULL != new)
		{
			if (tmp)
				tmp->next = new;
			new->prev = tmp;
			new->next = head;
			(head)->prev = new;
		}
	}	
}

void	ft_token_lstadd_next(t_token *head, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (head)
	{
		tmp = (head)->next;
		if (NULL != new)
		{
			(head)->next = new;
			new->prev = head;
			new->next = tmp;
			if (tmp)
				tmp->prev = new;
		}
	}
	
}

// int	main(void)
// {
// 	t_token *head;
// 	t_token	*my_head;

// 	head = NULL;
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str1"));
// 	// ft_token_lstadd_back(&head, ft_token_lstnew("str2"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str3"));
// 	// ft_token_lstadd_back(&head, ft_token_lstnew("str4"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str5"));
// 	my_head = head;
// 	while (head->next)
// 	{
// 		printf("%s\n", head->str_val);
// 		head = head->next;
// 	}
// 	printf("%s\n", head->str_val);
// 	// head = my_head;
// 	// ft_token_lstadd_front(&my_head, ft_token_lstnew("str0"));
// 	// ft_token_lstadd_back(&my_head, ft_token_lstnew("str5"));
// 	// head = head->next;
// 	// ft_token_lstadd_prev(&my_head->next, ft_token_lstnew("str2"));
// 	ft_token_lstadd_next(my_head->next, ft_token_lstnew("str4"));
// 	ft_token_lstadd_prev(my_head->next, ft_token_lstnew("str2"));
// 	printf("--------\n");
// 	while (head->prev)
// 	{
// 		printf("%s\n", head->str_val);
// 		head = head->prev;
// 	}
// 	printf("%s\n", head->str_val);
// 	printf("--------\n");
// 	while (head->next)
// 	{
// 		printf("%s\n", head->str_val);
// 		head = head->next;
// 	}
// 	printf("%s\n", head->str_val);
// }
