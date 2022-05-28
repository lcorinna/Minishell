/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:37:09 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 16:20:44 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_perror_wcds(t_info *data, char *file)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(SHELL, "\b\b: ");
	s2 = ft_strjoin(s1, file);
	free(s1);
	ft_putstr_fd(s2, 2);
	free(s2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	data->status = AMBIG_REDIR;
	return (data->status);
}

void	ft_get_dir_files(t_info *data)
{
	DIR				*curr_dir;
	struct dirent	*s_dir;

	curr_dir = opendir("./");
	s_dir = readdir(curr_dir);
	while (s_dir)
	{
		ft_lstadd_back(&data->dir_files, ft_lstnew(ft_strdup(s_dir->d_name)));
		s_dir = readdir(curr_dir);
	}
	closedir(curr_dir);
}

char	*ft_compare_filenames(t_info *data, char *str)
{
	int		ind;
	char	*filename;
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
