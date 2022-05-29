/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:18:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/29 16:51:41 by lcorinna         ###   ########.fr       */
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

static void	ft_get_dir_files(t_info *data)
{
	DIR				*curr_dir;
	struct dirent	*s_dir;

	ft_lstclear(&data->dir_files, free);
	curr_dir = opendir("./");
	while ((s_dir = readdir(curr_dir)))
		ft_lstadd_back(&data->dir_files, ft_lstnew(ft_strdup(s_dir->d_name)));
	closedir(curr_dir);
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		// printf("%s\n", data->dir_head->content);
		data->dir_head = data->dir_head->next;
	}
	// printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
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
		{
			return (filename);
		}
	}
	return (NULL);
}

char	*ft_do_wildcards_file(t_info *data, char *str)
{
	char	*s;
	t_list	*wcds;

	s = NULL;
	wcds = NULL;
	ft_get_dir_files(data);
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		s = ft_compare_filenames(data, str);
		if (s)
			ft_lstadd_back(&wcds, ft_lstnew(ft_strdup(s)));
		// printf("%s\n", s);
		data->dir_head = data->dir_head->next;
	}	
	if (!wcds)
	{}
	else if (ft_lstsize(wcds) == 1)
	{
		free(str);
		str = ft_strdup(wcds->content);
	}
	else
	{
		free(str);
		str = NULL;
	}
	ft_lstclear(&wcds, free);
	ft_lstclear(&data->dir_files, free);
	// printf("#######\n%s\n", str);
	return (str);
}

char	*ft_do_wildcards_argv(t_info *data, char *str)
{
	char	*s;
	char	*tmp;
	char	*res;

	s = NULL;
	tmp = NULL;
	res = ft_strdup("\0");
	ft_get_dir_files(data);
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		s = ft_compare_filenames(data, str);
		if (s)
		{
			tmp = res;
			res = ft_strjoin_three(tmp, s, " ");
			// printf("%s\n", res);
			free(tmp);
		}
		data->dir_head = data->dir_head->next;
	}
	res[ft_strlen(res) - 1] = '\0';
	// printf("%s\n", res);
	if (ft_strlen(res))
	{
		free(str);
		str = res;
	}
	ft_lstclear(&data->dir_files, free);
	return (str);
}
