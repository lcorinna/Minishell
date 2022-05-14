/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:58:31 by merlich           #+#    #+#             */
/*   Updated: 2022/05/14 23:59:21 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_perror(t_info *data, char *cmd)
{
	printf("%s\b\b: %s: command not found\n", SHELL, cmd);
	data->status = errno;
}

static void	ft_get_cmd_paths(t_info *data)
{
	data->envp_head = data->envp_list;
	while (data->envp_head)
	{
		if (!ft_strncmp(data->envp_head->key, "PATH", 4))
			break ;
		data->envp_head = data->envp_head->next;
	}
	if (NULL == data->envp_head)
		return ;
	data->path = ft_split(data->envp_head->value, ':');
}

static char	*ft_get_bin(char **path, char *bin)
{
	char	*tmp;
	char	*full_path;

	if (bin[0] == '/' && access(bin, X_OK))
		return (NULL);
	else if (!access(bin, X_OK))
		return (ft_strdup(bin));
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		full_path = ft_strjoin(tmp, bin);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path++;
	}
	return (NULL);
}

int	ft_check_words(t_info *data, int count)
{
	char	*cmd;

	cmd = data->token_head->str_val;
	if (!count)
	{
		if (data->token_head->type == WORD)
		{
			ft_get_cmd_paths(data);
			data->group_head->cmds_head->cmd_path = ft_get_bin(data->path, cmd);
			printf("%s\n",data->group_head->cmds_head->cmd_path);
			if (access(data->group_head->cmds_head->cmd_path, X_OK))
			{
				ft_perror(data, cmd);
				return (data->status);
			}
			count++;
		}
	}
	else
		data->group_head->cmds_head->cmd_argv = cmd; // join c cmd до (< > << >> |)
	return (0);
}

		// else if (data->token_head->type == WORD we already have cmd) // It can be flags '-' or args of cmd
		// 	// (error msg and return () + signal to continue main while loop)