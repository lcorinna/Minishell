/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/16 21:39:39 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//посчитать кол-во команд (чтобы понимать кол-во труб, нужны ли)
//если трубы нужны, то ухожу в ветвление с их созданием

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
	new->cmd_argv = argv;
	new->next = NULL;
	return (new);
}

void	test_zapolnenie(t_info *data)
{
	t_group	*tmp;
	t_cmds	*tmp1;
	t_cmds	*tmp2;

	tmp1 = ft_t_cmdsnew(0, 0, "bin/cp", "cp");
	tmp2 = ft_t_cmdsnew(0, 0, "bin/cat", "cat");
	tmp = malloc(sizeof(t_group));
	tmp->cmds_head = tmp1;
	tmp->next = NULL;  //  use "right" instead of "next"
	tmp1->next = tmp2;
	printf("1 - %p\n", tmp1); //del
	printf("2 - %p\n", tmp1->next); //del
	printf("tmp1.cmd_argv - %s\n", tmp1->cmd_argv); //del
	printf("tmp2.cmd_argv - %s\n\n", tmp1->next->cmd_argv); //del
	data->group_head = tmp;
}

void	ft_perror_exit_child(char *str, int error)
{
	perror(str);
	exit(error);
}

void	ft_pipe_one_cmd(t_info *data)
{
	data->exec->pipe = malloc((sizeof(int *) * 1));
	if (data->exec->pipe == NULL) //пишем об ошибке и exit
		ft_perror_exit_child("Inside child malloc error", MALLOC);
	data->exec->pipe[0] = malloc((sizeof(int *) * 2));
	if (data->exec->pipe[0] == NULL) //пишем об ошибке и exit
		ft_perror_exit_child("Inside child malloc error", MALLOC);
	if (data->group_head->cmds_head->infile != 0) //тогда читаем из infile
	{
		printf("HERE one cmd\n"); //del	
		if (dup2(data->group_head->cmds_head->infile, 0) == -1) //меняем infile
			ft_perror_exit_child("Inside child dup error", DUP);
		close(data->group_head->cmds_head->infile);
	}
	if (data->group_head->cmds_head->outfile != 1) //тогда читаем в outfile
	{
		if (dup2(data->group_head->cmds_head->outfile, 1) == -1) //меняем outfile
			ft_perror_exit_child("Inside child dup error", DUP);
		close(data->group_head->cmds_head->outfile);
	}
}

int	ft_exec_one_cmd(t_info	*data)
{
	int	status;

	data->exec->pid = fork();
	if (data->exec->pid == -1)
		return (1);
	else if (data->exec->pid == 0) //ребенок
	{
		if (data->group_head->cmds_head->infile != 0 || \
		data->group_head->cmds_head->outfile != 1) //создать трубу перенаправить
			ft_pipe_one_cmd(data);
		// if (проверить не билтын ли билтыны?) // БИЛТЫНЫ БИЛТЫНЫ БИЛТЫНЫ БИЛТЫНЫ
		// printf("HERE HERE HERE\n");
		// printf("%s\n", data->group_head->cmds_head->cmd_path);
		// printf("%s\n", data->group_head->cmds_head->cmd_argv);
		execve(data->group_head->cmds_head->cmd_path, \
		&data->group_head->cmds_head->cmd_argv, data->envp);
		ft_perror_exit_child("Inside child execve error", 1);
	}
	if (wait(&status) == -1)
		return (1);
	return (0);
}

int	ft_pipe_many_cmd(t_info	*data)
{
	int	i;
	int	tmp;

	tmp = data->exec->qtt_cmd;
	i = 0;
	data->exec->pipe = malloc(sizeof(int *) * (data->exec->qtt_cmd - 1));
	if (data->exec->pipe == NULL)
		return(1);
	while (tmp != 1)
	{
		data->exec->pipe[i] = malloc(sizeof(int) * 2);
		if (data->exec->pipe[i] == NULL)
			return (1);
		tmp--;
	}
	return (0);
}

int	ft_exec_many_cmd(t_info *data)
{
	int	status;

	ft_pipe_many_cmd(data);
	while (data->exec->n_child <= data->exec->qtt_cmd)
	{	
		data->pid = fork();
		if (data->pid == -1)
			ft_exit(data, 4);
		else if (data->pid == 0 && data->n_child == 0)
			ft_first_entry(data, envp, argv);
		else if (data->pid == 0 && data->n_child == data->qtt_cmd)
			ft_last_entry(data, envp, argv);
		else if (data->pid == 0)
			ft_routine(data, envp, argv);
		data->n_child++;
		data->n_cmd++;
	}
	ft_close_all_pipes(data);
	while (data->n_child > 0)
	{
		if (wait(&status) == -1)
			ft_exit(data, 8);
		data->n_child--;
	}
	return (0);
}

int	ft_preparation(t_info *data)
{
	t_cmds	*tmp;

	tmp = data->group_head->cmds_head;
	data->exec->qtt_cmd = 0;
	while (tmp)
	{
		printf("tmp->infile - %d\n", tmp->infile); //del
		printf("tmp->outfile - %d\n", tmp->outfile); //del
		printf("tmp1.cmd_path - %s\n", tmp->cmd_path); //del
		printf("tmp1.cmd_argv - %s\n\n", tmp->cmd_argv); //del
		tmp = tmp->next;
		data->exec->qtt_cmd++;
	}
	// data->exec->qtt_cmd--;
	printf("new->qtt_cmd - %d\n\n", data->exec->qtt_cmd); //del
	if (data->exec->qtt_cmd == 1) //одна команда, проверяем cmd_argv и исполняем
		if (ft_exec_one_cmd(data))
			return (1);
	// else if (data->exec->qtt_cmd > 1) //много команд, нужны трубы, идем их делать
	// 	if (ft_exec_many_cmd(data))
	// 		return (1);
	return (0);
}

int	ft_struct_exec(t_info *data)
{
	t_f_exec	*new; //структура для pipex

	new = malloc(sizeof(t_f_exec));
	if (new == NULL)
		return (1);
	new->qtt_cmd = 0; //зануляем, ну так на всякий
	new->pipe = NULL; //зануляем, ну так на всякий
	new->n_child = 0; //зануляем, ну так на всякий
	data->exec = new; //привязываем к основной структуре t_info
	return (0);
}

int	ft_executor(t_info *data)
{
	if (data->exec == NULL) //при первом заходе инициализирую структуру exec
		if (ft_struct_exec(data))
			return (1); //ошибка функции
	// test_zapolnenie(data);
	if (ft_preparation(data))
		return (1);
	printf("\nHERE\n"); //del
	// data->exec = NULL; почистить структуру перед выходом
	return (0);
}
