/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_one_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/30 19:08:17 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror_exit_child(char *str, int error)
{
	if (str != NULL)
		perror(str);
	exit(error);
}

void	ft_pipe_one_cmd(t_cmds *head)
{
	if (head->infile != 0) //тогда читаем из infile
	{
		if (dup2(head->infile, 0) == -1) //меняем infile
			ft_perror_exit_child("Inside dup error", DUP);
		close(head->infile);
	}
	if (head->outfile != 1) //тогда читаем в outfile
	{
		if (dup2(head->outfile, 1) == -1) //меняем outfile
			ft_perror_exit_child("Inside dup error", DUP);
		close(head->outfile);
	}
}

void	ft_birth_child(t_info *data, t_cmds *head)
{
	ft_signal(data, 2);
	data->exec->pid = fork();
	if (data->exec->pid == -1)
		ft_perror_exit_child("Inside child execve error", 1);
	else if (head->cmd_path == NULL && data->exec->pid == 0)
		exit(1);
	else if (data->exec->pid == 0) //ребенок
	{
		ft_signal(data, 3);
		if (head->infile != 0 || head->outfile != 1) //сделать dup2
			ft_pipe_one_cmd(head);
		ft_builtins_command(data, head->cmd_argv); //не билтын ли?
		data->status = execve(head->cmd_path, head->cmd_argv, data->envp);
		ft_perror_exit_child("Inside child execve error", 1);
	}
}

void	ft_waitpid(t_info *data, int pid)
{
	int	status;

	if (waitpid(pid, &status, WUNTRACED) == -1)
		ft_perror_exit_child("", 1);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			data->status = 131;
			ft_putstr_fd("Quit: 3\n", 1); //back slash
		}
		else if (WTERMSIG(status) == 2)
		{
			data->status = 132;
			ft_putstr_fd("\n", 1); //^C //yes | head // проверить
		}
	}
}

int	ft_exec_one_cmd(t_info	*data, t_cmds *head)
{
	int	control;

	control = ft_only_parent_need(data->group_head->cmds_head->cmd_argv);
	if (control == 0)
	{
		ft_birth_child(data, head);
		ft_waitpid(data, -1);
	}
	else if (control)
		ft_builtins_command(data, data->group_head->cmds_head->cmd_argv);
	return (0);
}
