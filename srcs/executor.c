/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/30 18:34:10 by lcorinna         ###   ########.fr       */
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

	if (head == NULL)
		return (1);
	tmp = head;
	data->exec->qtt_cmd = 0;
	while (tmp)
	{
		// printf("cmd.str - %s\n", tmp->cmd_str); //del
		tmp = tmp->next;
		data->exec->qtt_cmd++;
	}
	tmp = head;
	if (data->exec->qtt_cmd == 1) //одна команда, проверяем cmd_str и исполняем
	{
		if (tmp->cmd_path != NULL && ft_exec_one_cmd(data, head))
			return (1);
	}
	else if (data->exec->qtt_cmd > 1) //много команд, нужны трубы
	{
		if (ft_exec_many_cmd(data, head))
			return (1);
	}
	return (0);
}

// int	ft_check_operation(t_info *data, t_group *head)
// {
// 	int		res;
// 	t_group	*tmp;

// 	res = 0;
// 	tmp = head;
// 	while (tmp)
// 	{
// 		if (tmp->logical_operation == 10)
// 		{
// 			if (res == 0 || res == 10)
// 				res = 10;
// 			else
// 				res = 11; //оба 
// 		}
// 		else if (tmp->logical_operation == 9)
// 		{
// 			if (res == 0 || res == 9)
// 				res = 9;
// 			else
// 				res = 11; //оба
// 		}
// 		tmp = tmp->right;
// 	}
// 	return (res);
// }

// void	ft_only_ten(t_info *data, t_group *head)
// {
// 	t_group	*tmp;

// 	tmp = head;
// 	while (tmp)
// 	{
// 		ft_preparation(data, tmp->cmds_head);
// 		if (data->status == 0)
// 			break ;
// 		if (tmp->right != NULL)
// 			tmp = tmp->right->right;
// 	}
// }

// void	ft_only_nine(t_info *data, t_group *head)
// {
// 	t_group	*tmp;

// 	tmp = head;
// 	while (tmp)
// 	{	
// 		ft_preparation(data, tmp->cmds_head);
// 		if (tmp->right == NULL)
// 			break ;
// 		if (data->status != 0)
// 			break ;
// 		if (tmp->right != NULL)
// 			tmp = tmp->right->right;
// 	}
// }

// void	ft_both_operations(t_info *data)
// {
// 	t_group	*tmp;
// 	int		flag;

// 	tmp = data->group_head;
// 	flag = 0;
// 	while (tmp)
// 	{
// 		ft_preparation(data, tmp->cmds_head);
// 		if (tmp->right == NULL) //9
// 			break ;
// 		if (flag == 9 && data->status != 0) //9 &&
// 			break ;
// 		else if (flag == 10 && data->status == 0) //10 ||
// 		{
// 			if (tmp->right != NULL)
// 			{
// 				tmp = tmp->right->right;
// 				continue;
// 			}
// 		}
// 		tmp = tmp->right;
// 		if (tmp->logical_operation == 9)
// 			flag = 9;
// 		if (tmp->logical_operation == 10)
// 			flag = 10;
// 		if (tmp->right != NULL) //9
// 			tmp = tmp->right;
// 			// tmp = tmp->right->right;
// 	}
// 	printf("both options\n"); //del
// }

// void	ft_logical_operation(t_info *data, t_group *head)
// {
// 	int	branch;

// 	if (head == NULL)
// 		return ;
// 	branch = 0;
// 	branch = ft_check_operation(data, head);
// 	if (branch == 9) //&&
// 		ft_only_nine(data, head);
// 	if (branch == 10) //||
// 		ft_only_ten(data, head);
// 	if (branch == 0)
// 		ft_preparation(data, head->cmds_head);
// 	// else if (branch == 11) //оба
// 	// 	ft_both_operations(data);
// }

void	ft_executor(t_info *data, t_group *head)
{
	if (head == NULL)
		return ;
	// printf("\nhead - %d\n", head->logical_operation); //del
	// if (head->cmds_head != NULL)
	// 	printf("str - %s\n", head->cmds_head->cmd_str); //del
	// printf("HERE\n"); //del
	if (data->exec == NULL) //при первом заходе инициализирую структуру exec
		if (ft_struct_exec(data))
			ft_perror_exit_child("", 12);
	if (head)
	{
		ft_executor(data, head->left);
		// if (head->right == NULL && head->left == NULL)
		// {
		// printf("1\n"); //del
		// ft_preparation(data, data->group_head->cmds_head);
		if (head->logical_operation == 9 && data->status != 0)
			return ;
		else if (head->logical_operation == 10 && data->status == 0)
			return ;
		ft_preparation(data, head->cmds_head);
		// }
		// else if (data->group_head->right->logical_operation != 0)
		// {
		// 	printf("2\n"); //del
		// ft_logical_operation(data, head);
		// }
		ft_executor(data, head->right);
	}
	if (data->exec != NULL)
		ft_free_exec(data); //освобождаю exec перед выходом
}
