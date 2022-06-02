/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_new_elem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/06/01 22:07:06 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(n + 1);
	if (NULL == ptr)
		return (NULL);
	else
	{
		while (i < n)
		{
			ptr[i] = s[i];
			++i;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

int	ft_change_value(t_llist *llist, char *key, char *value)
{
	t_llist	*tmp;
	int		len;

	tmp = llist;
	len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, (len + 1)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	else if (ft_strncmp(key, tmp->key, (len + 1)) == 0)
	{
		free(tmp->value);
		tmp->value = value;
		free(key);
	}
	return (1);
}

void	ft_newelem_export(t_info *data, char *str)
{
	int		i;
	char	*key;
	char	*value;
	t_llist	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	key = ft_strndup(str, i);
	if (str[i] == '=')
		++i;
	value = ft_strdup(str + i);
	if (key == NULL || value == NULL)
		ft_perror_exit_child("", 12);
	if (ft_change_value(data->export, key, value))
		return ;
	new = ft_llstnew(key, value);
	if (new == NULL)
		ft_perror_exit_child("", 12);
	ft_llstadd_back(&data->export, new);
}

void	ft_newelem_env(t_info *data, char *str)
{
	int		i;
	char	*key;
	char	*value;
	t_llist	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	key = ft_strndup(str, i);
	if (str[i] == '=')
		++i;
	value = ft_strdup(str + i);
	if (key == NULL || value == NULL)
		ft_perror_exit_child("", 12);
	if (ft_change_value(data->envp_list, key, value))
		return ;
	new = ft_llstnew(key, value);
	if (new == NULL)
		ft_perror_exit_child("", 12);
	ft_llstadd_back(&data->envp_list, new);
}

void	ft_adding_to_struct(t_info *data, char **arr)
{
	int	i;
	int	put;

	i = 1;
	while (arr[i])
	{
		put = ft_check_arguments_export(data, arr[i]);
		if (put > 0)
		{
			ft_newelem_export(data, arr[i]);
			if (put == 2)
				ft_newelem_env(data, arr[i]);
		}
		i++;
	}
}
