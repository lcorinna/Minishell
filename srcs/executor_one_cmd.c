/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_one_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/19 16:23:14 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror_exit_child(char *str, int error)
{
	if (str != NULL)
		perror(str);
	exit(error);
}

void	ft_pipe_one_cmd(t_info *data)
{
	if (data->group_head->cmds_head->infile != 0) //тогда читаем из infile
	{
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

int	ft_my_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (i < (int) n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (i);
}

// void	ft_builtins_command(t_info	*data, char **arr)
// {
// 	if (ft_memcmp_l("echo", arr[0], 5) == 5) //echo with option -n
// 		ft_echo(arr);
// 	else if (ft_memcmp_l("cd", arr[0], 3) == 3) //cd with only a relative or absolute path

// 	else if (ft_memcmp_l("pwd", arr[0], 4) == 4) //pwd with no options

// 	else if (ft_memcmp_l("export", arr[0], 7) == 7) //export with no options

// 	else if (ft_memcmp_l("unset", arr[0], 6) == 6) //unset with no options

// 	else if (ft_memcmp_l("env", arr[0], 4) == 4) //env with no options or arguments

// 	else if (ft_memcmp_l("exit", arr[0], 5) == 5) //exit with no options

// 	else if (ft_memcmp_l("./minishell", arr[0], 12) == 12) //./minishell SHLVL=1
// 		ft_change_SHLVL(data);
// }

int	ft_exec_one_cmd(t_info	*data)
{
	int	status;

	data->exec->pid = fork();
	if (data->exec->pid == -1)
		return (1);
	else if (data->exec->pid == 0) //ребенок
	{
		if (data->group_head->cmds_head->infile != 0 || \
		data->group_head->cmds_head->outfile != 1) //сделать dup2
			ft_pipe_one_cmd(data);
		// ft_builtins_command(data, data->group_head->cmds_head->cmd_argv); //не билтын ли?
		execve(data->group_head->cmds_head->cmd_path, \
		data->group_head->cmds_head->cmd_argv, data->envp);
		ft_perror_exit_child("Inside child execve error", 1); //позже убрать
	}
	if (wait(&status) == -1) //родитель ждем дитя
		return (1);
	return (0);
}
