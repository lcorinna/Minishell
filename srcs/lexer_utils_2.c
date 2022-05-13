/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:51:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 12:05:19 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_token	*ft_token_last_but_one(t_token *head)
// {
// 	if (head != NULL)
// 	{
// 		while (head->next->next != NULL)
// 		{
// 			head = head->next;
// 		}
// 	}
// 	return (head);
// }

// void	ft_token_dellast(t_token **head)
// {
// 	t_token	*last;
// 	t_token *last_but_one;

// 	last_but_one = ft_token_last_but_one(*head);
// 	last = ft_token_lstlast(*head);
// 	last_but_one->next = NULL;
// 	// if (ft_strncmp(last->str_val, " ", ft_strlen(last->str_val)))
// 	free(last->str_val);
// 	free(last);
// }

void	ft_token_lstdelone(t_token *lst)
{
	if (NULL != lst)
	{
		free(lst->str_val);
		free(lst);
	}
}

void	ft_token_lstclear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		ft_token_lstdelone(tmp);
		// // if (ft_strncmp(tmp->str_val, " ", ft_strlen(tmp->str_val)))
		// free(tmp->str_val);
		// free(tmp);
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

void	ft_token_lstmerge_next(t_token *node)
{
	char	*old_str_val;
	t_token	*tmp;

	old_str_val = NULL;
	if (node != NULL)
	{
		tmp = node->next->next;
		old_str_val = node->str_val;
		node->str_val = ft_strjoin(node->str_val, node->next->str_val);
		free(old_str_val);
		ft_token_lstdelone(node->next);
		node->next = tmp;
		if (tmp != NULL)
			tmp->prev = node;
	}
}

// int	main(void)
// {
// 	t_token *head;
// 	t_token *my_head;

// 	head = NULL;
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str0"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str1"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str2"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew(">"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew(">"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str3"));
// 	ft_token_lstadd_back(&head, ft_token_lstnew("str4"));
// 	my_head = head;
// 	while (my_head)
// 	{
// 		printf("%s\n", my_head->str_val);
// 		my_head = my_head->next;
// 	}
// 	printf("\n");
// 	my_head = head;
// 	ft_token_lstmerge_next(my_head->next->next->next);
// 	while (my_head)
// 	{
// 		printf("%s\n", my_head->str_val);
// 		my_head = my_head->next;
// 	}
// }
