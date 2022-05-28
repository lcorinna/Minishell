/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/28 16:41:03 by lcorinna         ###   ########.fr       */
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

int	ft_preparation(t_info *data)
{
	t_cmds	*tmp;

	tmp = data->group_head->cmds_head;
	// printf("new->qtt_cmd - %d\n\n", data->exec->qtt_cmd); //del
	while (tmp)
	{
		// printf("tmp->infile - %d\n", tmp->infile); //del
		// printf("tmp->outfile - %d\n", tmp->outfile); //del
		// printf("tmp1.cmd_path - %s\n", tmp->cmd_path); //del
		// printf("tmp1.cmd_str - %s\n\n", tmp->cmd_str); //del
		tmp = tmp->next;
		data->exec->qtt_cmd++;
	}
	// printf("new->qtt_cmd - %d\n\n", data->exec->qtt_cmd); //del
	tmp = data->group_head->cmds_head;
	if (data->exec->qtt_cmd == 1) //одна команда, проверяем cmd_str и исполняем
	{
		if (tmp->cmd_path != NULL && ft_exec_one_cmd(data))
			return (1);
	}
	else if (data->exec->qtt_cmd > 1) //много команд, нужны трубы
	{
		if (ft_exec_many_cmd(data))
			return (1);
	}
	return (0);
}

int	ft_executor(t_info *data)
{
	if (data->exec == NULL) //при первом заходе инициализирую структуру exec
		if (ft_struct_exec(data))
			return (1); //ошибка функции
	if (data->group_head != NULL && ft_preparation(data))
		return (1);
	if (data->exec != NULL)
		ft_free_exec(data); //освобождаю exec перед выходом
	// printf("\nHERE\n"); //del
	return (0);
}
