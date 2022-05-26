/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/25 20:48:40 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ft_cmd_lstnew(void)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (NULL == new)
	{
		exit(ENOMEM);
	}
	new->infile = 0;
	new->outfile = 1;
	new->cmd_path = NULL;
	new->cmd_str = NULL;
	new->cmd_argv = NULL;
	new->next = NULL;
	return (new);
}

t_cmds	*ft_cmd_lstlast(t_cmds *head)
{
	if (head != NULL)
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
	}
	return (head);
}

void	ft_cmd_lstadd_front(t_cmds **head, t_cmds *new)
{
	if (NULL != new)
	{
		new->next = *head;
		*head = new;
	}
}

void	ft_cmd_lstadd_back(t_cmds **head, t_cmds *new)
{
	t_cmds	*lst_last;

	if (NULL != new)
	{
		lst_last = ft_cmd_lstlast(*head);
		if (lst_last == NULL)
		{
			ft_cmd_lstadd_front(head, new);
		}
		else
		{
			lst_last->next = new;
			new->next = NULL;
		}
	}
}

void	ft_cmd_lstclear(t_cmds **head)
{
	t_cmds	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		if (tmp->infile != 0)
		{
			close(tmp->infile);
			tmp->infile = 0;
		}
		if (tmp->outfile != 1)
		{
			close(tmp->outfile);
			tmp->outfile = 1;
		}
		ft_cleaning_str(tmp->cmd_path);
		ft_cleaning_str(tmp->cmd_str);
		ft_cleaning_array(tmp->cmd_argv);
		free(tmp);
		tmp = NULL;
	}
}
