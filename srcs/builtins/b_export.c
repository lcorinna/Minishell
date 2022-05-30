/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/30 15:58:49 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_sort(t_info *data)
{
	ft_need_sort(data->export);
	ft_print_exp(data->export);
}

void	ft_error_message_export(t_info *data, char *str)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	data->status = 1;
}

int	ft_check_arguments_export(t_info *data, char *arr)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (arr[i])
	{
		if (i == 0 && arr[i] >= '0' && arr[i] <= '9')
		{
			ft_error_message_export(data, arr);
			return (-1);
		}
		if ((arr[i] >= '!' && arr[i] <= '/') || \
			(arr[i] >= ':' && arr[i] <= '<') || \
			(arr[i] >= '>' && arr[i] <= '@') || \
			(arr[i] >= '[' && arr[i] <= '^') || \
			(arr[i] >= '{' && arr[i] <= '~'))
		{
			ft_error_message_export(data, arr);
			return (-1);
		}
		if (arr[i] == '=')
			res = 2;
		i++;
	}
	return (res);
}

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
		put = ft_check_arguments_export(data, arr[i]); //-1 ошибка, 1 exp, 2 оба
		if (put > 0)
		{
			ft_newelem_export(data, arr[i]);
			if (put == 2)
				ft_newelem_env(data, arr[i]);
		}
		i++;
	}
}

void	ft_export(t_info *data, char **arr)
{
	if (data->export == NULL)
		ft_cp_env_in_exp(data, data->envp_list);
	if (arr[0] != NULL && arr[1] == NULL)
		ft_print_sort(data);
	else if (arr[0] != NULL && arr[1] != NULL)
		ft_adding_to_struct(data, arr);
	data->envp_f = 1;
}
