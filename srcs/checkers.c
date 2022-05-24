/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:00:05 by merlich           #+#    #+#             */
/*   Updated: 2022/05/24 23:15:30 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_lexer(t_info *data)
{
	data->token_head = data->tokens;
	printf("------------------\n");
	while (data->token_head)
	{
		printf("string = %s\n", data->token_head->str_val);
		// printf("type == %d\n\n", data->token_head->type);
		data->token_head = data->token_head->next;
	}
	printf("------------------\n");
}

void	ft_checker(t_info *data)
{
	t_group	*grp;
	t_cmds	*tmp;
	int		k;
	int		m;
	char	**arr;

	k = 0;
	m = 0;
	arr = NULL;
	grp = data->group_head;
	while (grp)
	{
		tmp = grp->cmds_head;
		// printf("\nGroup %d:\n", k);
		// printf("############\n");
		// printf("priority = %d\n", grp->priority);
		// printf("log_oper = %d\n", grp->logical_operation);
		// printf("------------------------------------------\n");
		m = 0;
		arr = NULL;
		while (tmp)
		{
			// arr = tmp->cmd_argv;
			// printf("Cmd %d:\n", m);
			// printf("------------------\n");
			// printf("infile = %d\n", tmp->infile);
			// printf("outfile = %d\n", tmp->outfile);
			// printf("cmd_path[%d] = %s\n", m, tmp->cmd_path);
			// while (*arr)
			// {
			// 	printf("cmd_argv = %s\n", *arr);
			// 	arr++;
			// }
			tmp = tmp->next;
			m++;
			// printf("------------------\n");
		}
		// printf("############\n");
		grp = grp->right;
		k++;
	}
	// ft_in_order_traverse(data->root);
}
