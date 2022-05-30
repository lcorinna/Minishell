/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/30 19:04:23 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_exec(t_info *data)
{
	if (data->exec->pipe != NULL)
		ft_clean_array_int(data->exec->pipe, data->exec->qtt_cmd);
	free(data->exec);
	data->exec = NULL;
}

int	ft_clean_array_int(int **pipe, int qtt_cmd)
{
	int	i;

	i = 0;
	if (pipe)
	{
		// printf("qtt_cmd - %d\n", qtt_cmd); //del
		while (i < (qtt_cmd - 1))
		{
			free(pipe[i]);
			pipe[i] = NULL;
			i++;
			// printf("HERE 1\n"); //del
		}
		// printf("HERE 2\n"); //del
		free(pipe);
		pipe = NULL;
	}
	return (1);
}

void	ft_close_all_pipes(t_info *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (data->exec->qtt_cmd - 1))
	{
		j = 0;
		while (j != 2)
			close(data->exec->pipe[i][j++]);
		i++;
	}
}

void	ft_pipe_closure(t_info *data)
{
	int	i;
	int	j;

	i = 0;
	while (i != (data->exec->qtt_cmd - 1))
	{
		j = 0;
		while (j != 2)
		{
			if (data->exec->n_child != i && data->exec->n_child - 1 != i)
				close(data->exec->pipe[i][j]);
			j++;
		}
		i++;
	}
}
