/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/29 20:43:15 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ft_t_cmdsnew(int infile, int outfile, void *path, void *argv)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
	{
		return (NULL);
	}
	new->infile = infile;
	new->outfile = outfile;
	new->cmd_path = path;
	new->cmd_str = argv;
	new->next = NULL;
	return (new);
}

int	ft_struct_exec(t_info *data)
{
	t_f_exec	*new; //структура для pipex

	new = malloc(sizeof(t_f_exec));
	if (new == NULL)
		return (1);
	*new = (t_f_exec){}; // все занулиляем
	data->exec = new; //привязываем к основной структуре t_info
	return (0);
}

int	ft_preparation(t_info *data, t_cmds *head)
{
	t_cmds	*tmp;

	tmp = head;
	data->exec->qtt_cmd = 0;
	while (tmp)
	{
		tmp = tmp->next;
		data->exec->qtt_cmd++;
	}
	tmp = data->group_head->cmds_head;
	if (data->exec->qtt_cmd == 1) //одна команда, проверяем cmd_str и исполняем
	{
		if (tmp->cmd_path != NULL && ft_exec_one_cmd(data, head))
			return (1);
	}
	else if (data->exec->qtt_cmd > 1) //много команд, нужны трубы
	{
		if (ft_exec_many_cmd(data))
			return (1);
	}
	return (0);
}

int	ft_check_operation(t_info *data)
{
	int		res;
	t_group	*tmp;

	res = 0;
	tmp = data->group_head;
	while (tmp)
	{
		if (tmp->logical_operation == 10)
		{
			if (res == 0 || res == 10)
				res = 10;
			else
				res = 11; //оба 
		}
		else if (tmp->logical_operation == 9)
		{
			if (res == 0 || res == 9)
				res = 9;
			else
				res = 11; //оба
		}
		tmp = tmp->right;
	}
	return (res);
}

void	ft_only_ten(t_info *data)
{
	t_group	*tmp;

	tmp = data->group_head;
	while (tmp)
	{
		ft_preparation(data, tmp->cmds_head);
		if (data->status == 0)
			break ;
		if (tmp->right != NULL)
			tmp = tmp->right->right;
	}
}

void	ft_only_nine(t_info *data)
{
	t_group	*tmp;

	tmp = data->group_head;
	while (tmp)
	{	
		ft_preparation(data, tmp->cmds_head);
		if (tmp->right == NULL)
			break ;
		if (data->status != 0)
			break ;
		if (tmp->right != NULL)
			tmp = tmp->right->right;
	}
}

void	ft_logical_operation(t_info *data)
{
	int	branch;

	branch = ft_check_operation(data);
	if (branch == 9) //&&
		ft_only_nine(data);
	if (branch == 10) //||
		ft_only_ten(data);
	// else if (branch == 11) //оба
}

int	ft_executor(t_info *data)
{
	if (data->group_head == NULL)
		return (0);
	if (data->exec == NULL) //при первом заходе инициализирую структуру exec
		if (ft_struct_exec(data))
			ft_perror_exit_child("", 12);
	if (data->group_head->right == NULL && data->group_head->left == NULL)
		ft_preparation(data, data->group_head->cmds_head);
	else if (data->group_head->right->logical_operation != 0)
		ft_logical_operation(data);
	if (data->exec != NULL)
		ft_free_exec(data); //освобождаю exec перед выходом
	return (0);
}
