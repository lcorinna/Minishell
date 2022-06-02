/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 16:33:30 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_info *data, char **arr)
{
	char	tmp[1024];

	(void)arr;
	getcwd(tmp, 1024);
	ft_putendl_fd(tmp, 1);
	data->status = 0;
	exit(0);
}
