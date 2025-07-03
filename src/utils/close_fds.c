/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 03:47:03 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 03:53:04 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	close_pipe_fds(int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

void	close_and_reset(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_heredoc_backups(t_io *io)
{
	close_and_reset(&io->stdin_backup);
	close_and_reset(&io->stdout_backup);
}
