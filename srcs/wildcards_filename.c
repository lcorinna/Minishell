/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:18:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 22:50:08 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_do_comparision(t_info *data, char *str, t_list **wcds)
{
	char	*s;

	s = NULL;
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		s = ft_compare_filenames(data, str);
		if (s)
			ft_lstadd_back(wcds, ft_lstnew(ft_strdup(s)));
		data->dir_head = data->dir_head->next;
	}
}

char	*ft_do_wildcards_file(t_info *data, char *str)
{
	t_list	*wcds;

	wcds = NULL;
	ft_get_dir_files(data);
	ft_do_comparision(data, str, &wcds);
	if (ft_lstsize(wcds) == 1)
	{
		free(str);
		str = ft_strdup(wcds->content);
	}
	else if (ft_lstsize(wcds) > 1)
	{
		free(str);
		str = NULL;
	}
	ft_lstclear(&wcds, free);
	ft_lstclear(&data->dir_files, free);
	return (str);
}
