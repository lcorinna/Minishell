/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/29 17:45:16 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_without_argument(t_llist *envp_l, char *path)
{
	t_llist	*tmp;

	tmp = envp_l;
	while (tmp)
	{
		if (ft_memcmp_l("HOME", tmp->key, 5) == 5)
			break ;
		tmp = tmp->next;
	}
	if (ft_memcmp_l("HOME", tmp->key, 5) == 5)
	{
		path = tmp->value;
		chdir(path);
	}
	else
		return (1); //ошибка. Удалили HOME
	return (0);
}

void	ft_cd_pwd(t_llist *tmp, int flag, t_llist *envp_l)
{
	char	*key;
	char	*value;
	char	tmp1[1024];
	t_llist	*new;

	getcwd(tmp1, 1024);
	if (flag == 1)
	{
		free(tmp->value);
		tmp->value = ft_strdup(tmp1);
		if (tmp->value == NULL)
			ft_perror_exit_child("", 12);
	}
	else if (flag == 2) //делаем новый
	{
		key = ft_strdup("PWD");
		value = ft_strdup(tmp1);
		if (key == NULL || value == NULL)
			ft_perror_exit_child("", 12);
		new = ft_llstnew(key, value);
		if (!new)
			ft_perror_exit_child("", 12);
		ft_llstadd_back(&envp_l, new);
	}
}

void	ft_cd_oldpwd(t_llist *tmp, int flag, t_llist *envp_l, char *oldpwd)
{
	char	*key;
	char	*value;
	t_llist	*new;

	if (flag == 1)
	{
		printf("oldpwd - %s\n", oldpwd); //del
		free(tmp->value);
		tmp->value = oldpwd;
	}
	else if (flag == 2)
	{
		key = ft_strdup("OLDPWD");
		value = ft_strdup(oldpwd);
		free(oldpwd);
		if (key == NULL || value == NULL)
			ft_perror_exit_child("", 12);
		new = ft_llstnew(key, value);
		if (!new)
			ft_perror_exit_child("", 12);
		ft_llstadd_back(&envp_l, new);
	}
}

void	ft_added_pwd_oldpwd(char *oldpwd, t_llist *envp_l)
{
	int		pwd_f;
	int		oldpwd_f;
	t_llist	*tmp;

	tmp = envp_l;
	pwd_f = 1;
	oldpwd_f = 1;
	while (tmp)
	{
		if (ft_memcmp_l("PWD", tmp->key, 4) == 4)
		{
			ft_cd_pwd(tmp, 1, NULL);
			pwd_f = 0;
		}
		else if (ft_memcmp_l("OLDPWD", tmp->key, 4) == 4) //сделать его если не существуует
		{
			ft_cd_oldpwd(tmp, 1, NULL, oldpwd);
			oldpwd_f = 0;
		}
		tmp = tmp->next;
	}
	if (pwd_f == 1)
		ft_cd_pwd(NULL, 2, envp_l);
	if (oldpwd_f == 1)
		ft_cd_oldpwd(NULL, 2, envp_l, oldpwd);
}

void	ft_cd(t_info *data, char **arr)
{
	int		mistake;
	char	*oldpwd;
	char	*path;

	oldpwd = NULL;
	path = NULL;
	mistake = 0;
	ft_search_oldpwd(&oldpwd, data->envp_list);
	if (arr[1] == NULL)
	{
		mistake = ft_without_argument(data->envp_list, path);
		if (mistake == 1) //если 1, то ошибка
			ft_cd_error(data, arr, 1);
	}
	else
	{
		mistake = chdir(arr[1]); //пытаемся перейти в другую папку
		if (mistake == -1)
			ft_cd_error(data, arr, 2);
	}
	if (mistake == 0) //переписываем все PWD
		ft_added_pwd_oldpwd(oldpwd, data->envp_list);
	data->envp_f = 1;
}
