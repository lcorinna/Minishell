/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/13 19:10:49 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//посчитать кол-во команд (чтобы понимать кол-во труб, нужны ли)
//если трубы нужны, то ухожу в ветвление с их созданием

void	test_zapolnenie(t_info *data)
{
	t_group	tmp;
	t_cmds	tmp1;
	t_cmds	tmp2;

	tmp2.infile = 0;
	tmp2.outfile = 0;
	tmp2.cmd_path = "bin/cp";
	tmp2.cmd_argv = "cp";
	tmp2.next = NULL;

	tmp1.infile = 0;
	tmp1.outfile = 0;
	tmp1.cmd_path = "bin/cat";
	tmp1.cmd_argv = "cat";
	printf("1 - %p\n", tmp1.next); //del
	tmp1.next = &tmp2;
	printf("2 - %p\n", tmp1.next); //del
	printf("tmp1.cmd_argv - %s\n", tmp1.cmd_argv); //del
	printf("tmp2.cmd_argv - %s\n\n", tmp1.next->cmd_argv); //del
	data->group_head = &tmp;
	// printf("data->group_head - %p\n", data->group_head); //del
	data->group_head->cmds_head = &tmp1;
	// printf("tmp1.cmd_argv - %s\n", data->group_head->cmds_head->cmd_argv); //del
	// printf("tmp2.cmd_argv - %s\n", data->group_head->cmds_head->next->cmd_argv); //del
}

int	ft_preparation(t_info *data)
{
	t_cmds		*tmp;
	t_f_exec	new; //структура для pipex
	int			i;

	new = (t_f_exec){};
	i = 0;
	data->exec = &new;
	tmp = data->group_head->cmds_head;
	while (tmp)
	{
		printf("i - %d\n", i); //del
		printf("tmp - %p\n", tmp); //del
		printf("tmp1.cmd_argv - %s\n", tmp->cmd_argv); //del
		printf("cmd %p\n\n", tmp->cmd_argv); //del
		tmp = tmp->next;
		i++;
	}
	printf("\ni last - %d\n", i); //del
	return (0);
}

int	ft_executor(t_info *data)
{
	int	i;

	printf("\nstart executor\n"); //del
	test_zapolnenie(data);
	printf("tmp1.cmd_argv - %s\n", data->group_head->cmds_head->cmd_argv); //del
	printf("tmp2.cmd_argv - %s\n", data->group_head->cmds_head->next->cmd_argv); //del
	// data->group_head->cmds_head = data->group_head->cmds_head->next;
	// printf("tmp1.cmd_argv - %s\n", data->group_head->cmds_head->cmd_argv); //del
	printf("\nHERE\n"); //del
	ft_preparation(data);
	i = 0;
	return (0);
}
