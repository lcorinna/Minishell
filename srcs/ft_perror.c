/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:57:39 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 20:14:17 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_perror_token(t_info *data, char *token_name)
{
	char	*s;
	char	*tmp;

	tmp = ft_strjoin(SHELL, "\b\b: syntax error near unexpected token `");
	s = ft_strjoin_three(tmp, token_name, "'\n");
	free(tmp);
	ft_putstr_fd(s, 2);
	free(s);
	data->status = TOKEN_ERROR;
	return (data->status);
}

int	ft_perror_eof(t_info *data)
{
	char	*s;
	char	*tmp;

	tmp = ft_strjoin("\x1b[F> ", SHELL);
	s = ft_strjoin(tmp, "\b\b: syntax error: unexpected end of file\n");
	free(tmp);
	ft_putstr_fd(s, 2);
	free(s);
	data->status = TOKEN_ERROR;
	return (data->status);
}

int	ft_perror_file(t_info *data, char *infile)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(SHELL, "\b\b: ");
	s2 = ft_strjoin(s1, infile);
	free(infile);
	free(s1);
	perror(s2);
	free(s2);
	data->status = errno;
	return (data->status);
}

int	ft_perror_symbols(t_info *data, char *symbol)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(SHELL, "\b\b: ");
	s2 = ft_strjoin(s1, symbol);
	free(s1);
	ft_putstr_fd(s2, 2);
	free(s2);
	data->status = SYMBOLS_ERROR;
	return (data->status);
}

int	ft_perror_cmd(t_info *data, char *cmd)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(SHELL, "\b\b: ");
	s2 = ft_strjoin(s1, cmd);
	free(s1);
	ft_putstr_fd(s2, 2);
	free(s2);
	ft_putstr_fd(": command not found\n", 2);
	data->status = CMD_NOT_FOUND;
	return (data->status);
}
