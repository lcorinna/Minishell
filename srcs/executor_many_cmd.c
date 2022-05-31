/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_many_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:02:28 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 17:27:07 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_routine(t_info *data, t_cmds	*tmp)
{
	ft_signal(data, 3);
	close(data->exec->pipe[data->exec->n_child - 1][1]);
	close(data->exec->pipe[data->exec->n_child][0]);
	ft_pipe_closure(data);
	if (tmp->infile != 0)
		ft_dup_with_zero(tmp->infile);
	else if (tmp->infile == 0)
	{
		if (dup2(data->exec->pipe[data->exec->n_child - 1][0], 0) == -1)
			ft_perror_exit_child("Inside child dup error", DUP);
	}
	if (tmp->outfile != 1)
		ft_dup_with_one(tmp->outfile);
	else if (tmp->outfile == 1)
	{
		if (dup2(data->exec->pipe[data->exec->n_child][1], 1) == -1)
			ft_perror_exit_child("Inside child dup error", DUP);
	}
	close(data->exec->pipe[data->exec->n_child - 1][0]);
	close(data->exec->pipe[data->exec->n_child][1]);
	ft_builtins_command(data, tmp->cmd_argv);
	if (ft_only_parent_need(tmp->cmd_argv))
		exit (1);
	data->status = execve(tmp->cmd_path, tmp->cmd_argv, data->envp);
	ft_perror_exit_child("Inside child execve error", 1);
}

void	ft_last_entry(t_info *data, t_cmds	*tmp)
{
	ft_signal(data, 3);
	close(data->exec->pipe[data->exec->n_child - 1][1]);
	ft_pipe_closure(data);
	if (tmp->infile != 0)
		ft_dup_with_zero(tmp->infile);
	else if (tmp->infile == 0)
	{
		if (dup2(data->exec->pipe[data->exec->n_child - 1][0], 0) == -1)
			ft_perror_exit_child("Inside child dup error", DUP);
	}
	if (tmp->outfile != 1)
		ft_dup_with_one(tmp->outfile);
	close(data->exec->pipe[data->exec->n_child - 1][0]);
	ft_builtins_command(data, tmp->cmd_argv);
	if (ft_only_parent_need(tmp->cmd_argv))
		exit (1);
	data->status = execve(tmp->cmd_path, tmp->cmd_argv, data->envp);
	ft_perror_exit_child("Inside last child execve error", 1);
}

void	ft_first_entry(t_info *data, t_cmds	*tmp)
{
	ft_signal(data, 3);
	close(data->exec->pipe[data->exec->n_child][0]);
	ft_pipe_closure(data);
	if (tmp->infile != 0)
		ft_dup_with_zero(tmp->infile);
	if (tmp->outfile != 1)
	{
		if (dup2(tmp->outfile, 1) == -1)
			ft_perror_exit_child("Inside child dup error", DUP);
		close(tmp->outfile);
	}
	else if (tmp->outfile == 1)
	{
		if (dup2(data->exec->pipe[data->exec->n_child][1], 1) == -1)
			ft_perror_exit_child("Inside child dup error", DUP);
	}
	close(data->exec->pipe[data->exec->n_child][1]);
	ft_builtins_command(data, tmp->cmd_argv);
	if (ft_only_parent_need(tmp->cmd_argv))
		exit (1);
	data->status = execve(tmp->cmd_path, tmp->cmd_argv, data->envp);
	ft_perror_exit_child("Inside first child execve error", 1);
}

void	ft_exec_many_cmd(t_info *data, t_cmds *head)
{
	t_cmds	*tmp;

	ft_pipe_many_cmd(data);
	tmp = head;
	while (tmp)
	{	
		ft_signal(data, 2);
		data->exec->pid = fork();
		if (data->exec->pid == -1)
			ft_perror_exit_child("", 1);
		else if (tmp->cmd_path == NULL && data->exec->pid == 0)
			exit(1);
		else if (data->exec->pid == 0 && data->exec->n_child == 0)
			ft_first_entry(data, tmp);
		else if (data->exec->pid == 0 && \
							data->exec->n_child == (data->exec->qtt_cmd - 1))
			ft_last_entry(data, tmp);
		else if (tmp->cmd_path != NULL && data->exec->pid == 0)
			ft_routine(data, tmp);
		data->exec->n_child++;
		tmp = tmp->next;
	}
	ft_close_all_pipes(data);
	while (--data->exec->n_child >= 0)
		ft_waitpid(data, -1);
}
