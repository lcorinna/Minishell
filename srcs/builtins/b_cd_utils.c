/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/06/01 13:13:47 by lcorinna         ###   ########.fr       */
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
		if (!ft_strncmp("PWD", tmp->key, 4))
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

void	ft_print_shell(char *str, char *shell)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	write(2, shell, ft_strlen(shell));
	write(2, "\b\b", 2);
}

void	ft_cd_error(t_info *data, char **arr, int flag, char *oldpwd)
{
	free(oldpwd);
	if (flag == 1)
	{
		ft_print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: HOME not set \n", 2);
	}
	else if (flag == 2)
	{
		ft_print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->status = 1;
}
