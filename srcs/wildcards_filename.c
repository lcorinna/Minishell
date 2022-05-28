/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 23:18:06 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 16:35:55 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("%s\n", wcds->content);
		data->dir_head = data->dir_head->next;
	}
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
	return (str);
}
