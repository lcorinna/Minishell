/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 19:38:32 by lcorinna         ###   ########.fr       */
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

void	ft_get_and_check_cmd(t_info *data, t_cmds *tmp)
{
	char	**cmd_paths;

	cmd_paths = ft_get_cmd_paths(data);
	tmp->cmd_path = ft_get_bin(cmd_paths, tmp->cmd_path);
	ft_cleaning_array(cmd_paths);
	if (!tmp->cmd_path)
		ft_perror_cmd(data, tmp->cmd_path);
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
		if (!ft_check_builtins(data, tmp))
			ft_get_and_check_cmd(data, tmp);
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
		ft_exec_many_cmd(data, head);
	return (0);
}

void	ft_executor(t_info *data, t_group *head)
{
	if (head == NULL)
		return ;
	if (data->exec == NULL) //при первом заходе инициализирую структуру exec
		if (ft_struct_exec(data))
			ft_perror_exit_child("", 12);
	if (head)
	{
		ft_executor(data, head->left);
		if (head->logical_operation == 9 && data->status != 0)
			return ;
		else if (head->logical_operation == 10 && data->status == 0)
			return ;
		ft_preparation(data, head->cmds_head);
		ft_executor(data, head->right);
	}
	if (data->exec != NULL)
		ft_free_exec(data); //освобождаю exec перед выходом
}
