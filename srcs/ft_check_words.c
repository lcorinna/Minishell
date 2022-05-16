/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:58:31 by merlich           #+#    #+#             */
/*   Updated: 2022/05/16 22:16:59 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_get_cmd_paths(t_info *data)
{
	data->envp_head = data->envp_list;
	while (data->envp_head && ft_strncmp(data->envp_head->key, "PATH", 4))
	{
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

static int	ft_check_builtins(t_info *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(data->token_head->str_val);
	while (data->res_words[i])
	{
		if (!ft_strncmp(data->res_words[i], data->token_head->str_val, len))
			return (++i);
		i++;
	}
	return (0);
}

int	ft_check_cmd_path(t_info *data)
{
	char	*cmd;

	cmd = data->token_head->str_val;
	if (data->token_head->type == WORD)
	{
		if (!ft_check_builtins(data))
		{
			ft_get_cmd_paths(data);
			data->cmds_head->cmd_path = ft_get_bin(data->path, cmd);
			// printf("%s\n", data->cmds_head->cmd_path);
			if (!data->cmds_head->cmd_path)
			{
				printf("%s\b\b: %s: command not found\n", SHELL, cmd);
				data->status = errno;
				return (data->status);
			}
		}
		else
			data->cmds_head->cmd_path = ft_strdup(cmd);
		data->cmds_head->cmd_argv = ft_strdup(data->cmds_head->cmd_path);
		data->token_head = data->token_head->next;
	}
	return (0);
}

int	ft_check_cmd_argv(t_info *data)
{
	char	*argv;
	char	*tmp;

	argv = data->token_head->str_val;
	tmp = data->cmds_head->cmd_argv;
	if (data->token_head->type == WORD)
	{
		data->cmds_head->cmd_argv = ft_strjoin_three(tmp, " ", argv);
		free(tmp);
		printf("%s\n", data->cmds_head->cmd_argv);
		data->token_head = data->token_head->next;
	}
	return (0);
}
