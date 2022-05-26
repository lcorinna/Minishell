/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/25 19:09:31 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_search_oldpwd(char **oldpwd, t_llist *envp_l)
{
	t_llist	*tmp;
	char	*new;
	char	tmp1[1024];

	tmp = envp_l;
	new = NULL;
	while (tmp)
	{
		if (ft_memcmp_l("PWD", tmp->key, 4) == 4)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		*oldpwd = ft_strdup(tmp->value);
	else if (tmp == NULL)
	{
		getcwd(tmp1, 1024);
		*oldpwd = ft_strdup(tmp1);
	}
	if (*oldpwd == NULL)
		ft_perror_exit_child("", 12);
}

void	ft_cd_error(char **arr, int flag)
{
	if (flag == 1)
		ft_putstr_fd("minishell: cd: HOME not set \n", 2);
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
