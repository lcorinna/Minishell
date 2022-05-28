/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:00:05 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 17:47:40 by lcorinna         ###   ########.fr       */
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
		data->token_head = data->token_head->next;
	}
	printf("------------------\n");
}

static void	ft_print_groups_elems(t_group *grp, t_cmds *tmp)
{
	int	m;

	m = 0;
	while (tmp)
	{
		if (grp->logical_operation == 9)
			printf("&&\n");
		else if (grp->logical_operation == 10)
			printf("||\n");
		printf("tmp->cmd_str[%d] = %s\n\n", m, tmp->cmd_str);
		tmp = tmp->next;
		m++;
	}
}

void	ft_check_parser(t_info *data)
{
	t_group	*grp;
	t_cmds	*tmp;
	int		k;

	k = 0;
	grp = data->group_head;
	while (grp)
	{
		tmp = grp->cmds_head;
		printf("\nGroup %d:\n", k);
		printf("adress = %p:\n", grp);
		printf("############\n");
		printf("level = %d\n", grp->nesting_level);
		ft_print_groups_elems(grp, tmp);
		grp = grp->right;
		k++;
	}
}

void	ft_check_bin_tree(t_group *root)
{
	if (root)
	{
		ft_check_bin_tree(root->left);
		if (root->logical_operation == 9)
			printf("&&\n");
		if (root->logical_operation == 10)
			printf("||\n");
		if (root->logical_operation == 0)
		{
			if (root->cmds_head)
				printf("%s\n", root->cmds_head->cmd_str);
		}
		ft_check_bin_tree(root->right);
	}
}
