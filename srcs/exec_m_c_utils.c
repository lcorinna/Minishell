/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_m_c_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:02:28 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 17:27:13 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_many_cmd(t_info	*data)
{
	int	i;
	int	t_qtt_cmd;

	t_qtt_cmd = data->exec->qtt_cmd;
	i = 0;
	data->exec->pipe = malloc(sizeof(int *) * (data->exec->qtt_cmd - 1));
	if (data->exec->pipe == NULL)
		ft_perror_exit_child("", 12);
	while (i < (t_qtt_cmd - 1))
	{
		data->exec->pipe[i] = malloc(sizeof(int) * 2);
		if (data->exec->pipe[i] == NULL)
			ft_perror_exit_child("", 12);
		i++;
	}
	i = 0;
	while (i < (t_qtt_cmd - 1))
	{
		if (pipe(data->exec->pipe[i]))
			ft_perror_exit_child("", 1);
		i++;
	}
}

void	ft_dup_with_zero(int infile)
{
	if (dup2(infile, 0) == -1)
		ft_perror_exit_child("Inside child dup error", DUP);
	close(infile);
}

void	ft_dup_with_one(int outfile)
{
	if (dup2(outfile, 1) == -1)
		ft_perror_exit_child("Inside child dup error", DUP);
	close(outfile);
}
