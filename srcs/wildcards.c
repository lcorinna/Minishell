/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:18:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/22 23:41:01 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_get_files(t_info *data)
{
	DIR				*curr_dir;
	struct dirent	*s_dir;

	curr_dir = opendir("./");
	while ((s_dir = readdir(curr_dir)))
		ft_lstadd_back(&data->dir_files, ft_lstnew(ft_strdup(s_dir->d_name)));
	closedir(curr_dir);
}

static char	*ft_compare_filenames(t_info *data, char *str)
{
	int		ind;
	char 	*filename;
	char	*tmp;

	ind = ft_search(str, '*');
	filename = data->dir_head->content;
	tmp = NULL;
	if (!ft_strncmp(filename, str, ind))
	{
		tmp = ft_strrchr(filename, str[ind + 1]);
		if (tmp && !ft_strncmp(tmp, str + ind + 1, ft_strlen(str) - ind))
			return (filename);
	}
	return (NULL);
}

char	*ft_do_wildcard(t_info *data, char *str)
{
	int		ind;
	char	*s;
	char	*tmp;
	char	*wcds;

	ind = 0;
	s = NULL;
	tmp = NULL;
	wcds = "\0";
	ft_get_files(data);
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		s = ft_compare_filenames(data, str);
		if (s)
		{
			tmp = wcds;
			wcds = ft_strjoin_three(wcds, s, " ");
			if (tmp[0] != '\0')  // if (ft_strncmp(tmp, "\0", 1))
				free(tmp);
		}
		data->dir_head = data->dir_head->next;
	}
	if (wcds)
		str = wcds;
	return (str);
}
