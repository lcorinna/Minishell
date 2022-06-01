/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:52:50 by lcorinna          #+#    #+#             */
/*   Updated: 2022/06/01 13:13:15 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	i;
	char	*new_str;

	i = -1;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (NULL == new_str)
		return (NULL);
	while (s1[++i] != '\0')
		new_str[i] = s1[i];
	while (*s2 != '\0')
	{
		new_str[i++] = *s2;
		s2++;
	}
	while (*s3 != '\0')
	{
		new_str[i++] = *s3;
		s3++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	ft_added_shlvl(t_info *data, t_llist **new)
{
	char	*key;
	char	*value;

	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	if (key == NULL || value == NULL)
		ft_error_exit(data, 1);
	(*new) = ft_llstnew(key, value);
	if (!new)
		ft_error_exit(data, 1);
}

void	ft_need_shlvl(t_info *data)
{
	t_llist	*new;

	new = NULL;
	ft_added_shlvl(data, &new);
	ft_llstadd_back(&data->envp_list, new);
}

void	ft_check_shlvl(t_info *data)
{
	t_llist	*tmp;
	int		lvl;
	int		flag;

	flag = 1;
	tmp = data->envp_list;
	while (tmp)
	{
		if (!ft_strncmp("SHLVL", tmp->key, 6))
		{
			lvl = ft_atoi(tmp->value);
			lvl++;
			free(tmp->value);
			tmp->value = ft_itoa(lvl);
			if (tmp->value == NULL)
				ft_error_exit(data, 1);
			flag = 0;
		}
		tmp = tmp->next;
	}
	if (flag == 1)
		ft_need_shlvl(data);
}
