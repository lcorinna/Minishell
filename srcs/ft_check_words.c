/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:58:31 by merlich           #+#    #+#             */
/*   Updated: 2022/05/24 22:48:23 by merlich          ###   ########.fr       */
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

	if (bin && bin[0] == '/' && access(bin, X_OK))
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
		if (!ft_strncmp(data->res_words[i], data->token_head->str_val, len + 1))
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
			ft_cleaning_array(data->path);
			data->path = NULL;
			if (!data->cmds_head->cmd_path)
			{
				return (ft_perror_cmd(data, cmd));
			}
		}
		else
			data->cmds_head->cmd_path = ft_strdup(cmd);
		data->cmds_head->cmd_str = ft_strdup(data->cmds_head->cmd_path);
		data->token_head = data->token_head->next;
	}
	return (0);
}

int	ft_check_cmd_str(t_info *data)
{
	char	*argv;
	char	*tmp;

	argv = ft_strdup(data->token_head->str_val);
	tmp = data->cmds_head->cmd_str;
	if (data->token_head->type == WORD)
	{
		if (ft_strchr(argv, '*'))
			argv = ft_do_wildcards_argv(data, argv);
		data->cmds_head->cmd_str = ft_strjoin_three(tmp, " ", argv);
		free(tmp);
		free(argv);
		printf("%s\n", data->cmds_head->cmd_str);
		data->token_head = data->token_head->next;
	}
	return (0);
}
