/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:58:31 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 18:39:22 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_cmd_paths(t_info *data)
{
	char	**ptr;

	ptr = NULL;
	data->envp_head = data->envp_list;
	while (data->envp_head && ft_strncmp(data->envp_head->key, "PATH", 4))
	{
		data->envp_head = data->envp_head->next;
	}
	if (data->envp_head)
		ptr = ft_split(data->envp_head->value, ':');
	return (ptr);
}

char	*ft_get_bin(char **path, char *bin)
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

int	ft_check_builtins(t_info *data, t_cmds *head)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(head->cmd_path);
	while (data->res_words[i])
	{
		if (!ft_strncmp(data->res_words[i], head->cmd_path, len + 1))
			return (++i);
		i++;
	}
	return (0);
}

int	ft_check_cmd_path(t_info *data)
{
	char	*cmd;
	// char	**cmd_paths;

	if (data->token_head->type == WORD)
	{
		cmd = data->token_head->str_val;
		// if (!ft_check_builtins(data))
		// {
		// 	cmd_paths = ft_get_cmd_paths(data);
		// 	data->cmds_head->cmd_path = ft_get_bin(cmd_paths, cmd);
		// 	ft_cleaning_array(cmd_paths);
		// 	if (!data->cmds_head->cmd_path)
		// 		return (ft_perror_cmd(data, cmd));
		// }
		// else
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

	if (data->token_head->type == WORD)
	{
		argv = ft_strdup(data->token_head->str_val);
		tmp = data->cmds_head->cmd_str;
		if (ft_strchr(argv, '*'))
			argv = ft_do_wildcards_argv(data, argv);
		data->cmds_head->cmd_str = ft_strjoin_three(tmp, " ", argv);
		free(tmp);
		free(argv);
		data->token_head = data->token_head->next;
	}
	return (0);
}
