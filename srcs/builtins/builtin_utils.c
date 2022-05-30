/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:28:23 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/30 19:18:49 by lcorinna         ###   ########.fr       */
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
	if (ft_memcmp_l("exit", arr[0], 5) == 5)
		return (1);
	else if (ft_memcmp_l("cd", arr[0], 3) == 3)
		return (1);
	else if (ft_memcmp_l("export", arr[0], 7) == 7)
		return (1);
	else if (ft_memcmp_l("unset", arr[0], 6) == 6)
		return (1);
	return (0);
}

int	ft_builtins_command(t_info *data, char **arr)
{
	if (ft_memcmp_l("exit", arr[0], 5) == 5) //exit with no options
		ft_exit(data, arr);
	else if (ft_memcmp_l("cd", arr[0], 3) == 3) //cd with only a relative or absolute path
		ft_cd(data, arr);
	else if (ft_memcmp_l("export", arr[0], 7) == 7) //export with no options
		ft_export(data, arr);
	else if (ft_memcmp_l("unset", arr[0], 6) == 6) //unset with no options
		ft_unset(data, data->envp_list, arr);
	else if (ft_memcmp_l("echo", arr[0], 5) == 5) //echo with option -n
		ft_echo(arr);
	else if (ft_memcmp_l("pwd", arr[0], 4) == 4) //pwd with no options
		ft_pwd(arr);
	else if (ft_memcmp_l("env", arr[0], 4) == 4) //env with no options or arguments
		ft_env(data);
	else if (ft_memcmp_l("./minishell", arr[0], 12) == 12) //./minishell SHLVL=1
	{
		ft_array_envp(data);
		return (0);
	}
	return (1);
}
