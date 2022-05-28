/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcards_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:04:25 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 16:14:22 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_fullfill_comparision(t_info *data, char *str)
{
	char	*s;
	char	*tmp;
	char	*res;

	s = NULL;
	tmp = NULL;
	res = ft_strdup("\0");
	data->dir_head = data->dir_files;
	while (data->dir_head)
	{
		s = ft_compare_filenames(data, str);
		if (s)
		{
			tmp = res;
			res = ft_strjoin_three(tmp, s, " ");
			free(tmp);
		}
		data->dir_head = data->dir_head->next;
	}
	return (res);
}

char	*ft_do_wildcards_argv(t_info *data, char *str)
{
	char	*res;

	res = NULL;
	ft_get_dir_files(data);
	res = ft_fullfill_comparision(data, str);
	res[ft_strlen(res) - 1] = '\0';
	if (ft_strlen(res))
	{
		free(str);
		str = res;
	}
	return (str);
}
