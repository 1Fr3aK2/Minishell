/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:33 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/04 16:59:21 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	close_io_fds(t_io *io)
{
	if (!io)
		return ;
	close(io->stdout_backup);
	close(io->stdin_backup);
}

void	close_fds(int i)
{
	i = 3;
	while (i < FOPEN_MAX)
	{
		close(i);
		i++;
	}
}

void	close_pipe_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

char	*reverse_strchr(char *str, int c)
{
	char	*pos;
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	pos = ft_strchr(str, c);
	if (!pos)
		return (NULL);
	len = pos - str;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, len);
	new[len] = '\0';
	return (new);
}

void	change_shlvl(char ***env, char *name)
{
	int		i;
	char	*value;
	char	*new_val;

	if (!env || !*env)
		return ;
	i = 0;
	value = (ft_itoa(ft_atoi(get_env(name, *env)) + 1));
	if (!value)
		return ;
	new_val = ft_strjoin("SHLVL=", value);
	free(value);
	if (!new_val)
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp("SHLVL=", (*env)[i], ft_strlen("SHLVL=")) == 0)
		{
			free((*env)[i]);
			(*env)[i] = new_val;
		}
		i++;
	}
}
