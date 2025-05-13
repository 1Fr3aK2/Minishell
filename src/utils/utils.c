/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:33 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/13 18:28:30 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

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
