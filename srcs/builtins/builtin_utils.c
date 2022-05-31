/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:28:23 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 19:43:03 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_memcmp_l(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (i < (int) n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (i);
}

int	ft_only_parent_need(char **arr)
{
	if (!ft_strncmp("exit", arr[0], 5) || !ft_strncmp("EXIT", arr[0], 5))
		return (1);
	else if (!ft_strncmp("cd", arr[0], 3) || !ft_strncmp("CD", arr[0], 3))
		return (1);
	else if (!ft_strncmp("export", arr[0], 7) \
										|| !ft_strncmp("EXPORT", arr[0], 7))
		return (1);
	else if (!ft_strncmp("unset", arr[0], 6) || !ft_strncmp("UNSET", arr[0], 6))
		return (1);
	return (0);
}

int	ft_builtins_command(t_info *data, char **arr)
{
	if (!ft_strncmp("exit", arr[0], 5) || !ft_strncmp("EXIT", arr[0], 5))
		ft_exit(data, arr);
	else if (!ft_strncmp("cd", arr[0], 3) || !ft_strncmp("CD", arr[0], 3))
		ft_cd(data, arr);
	else if (!ft_strncmp("export", arr[0], 7) \
										|| !ft_strncmp("EXPORT", arr[0], 7))
		ft_export(data, arr);
	else if (!ft_strncmp("unset", arr[0], 6) || !ft_strncmp("UNSET", arr[0], 6))
		ft_unset(data, data->envp_list, arr);
	else if (!ft_strncmp("echo", arr[0], 5) || !ft_strncmp("ECHO", arr[0], 5))
		ft_echo(data, arr);
	else if (!ft_strncmp("pwd", arr[0], 4) || !ft_strncmp("PWD", arr[0], 4))
		ft_pwd(data, arr);
	else if (!ft_strncmp("env", arr[0], 4) || !ft_strncmp("env", arr[0], 4))
		ft_env(data);
	else if (!ft_strncmp("./minishell", arr[0], 12))
		return (ft_array_envp(data));
	return (1);
}
