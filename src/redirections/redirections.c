/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/28 15:46:51 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_output_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (0);
	if (io->fd_out > 2)
		close(io->fd_out);
	io->fd_out = open(io->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		perror(io->file);
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_input_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (0);
	if (io->fd_in > 2)
		close(io->fd_in);
	io->fd_in = open(io->file, O_RDONLY);
	if (io->fd_in == -1)
	{
		perror(io->file);
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_append_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (0);
	if (io->fd_out > 2)
		close(io->fd_out);
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
	{
		perror(io->file);
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}

void	setup_stdout(int out)
{
	if (out != -1)
	{
		dprintf(2, "[DEBUG setup_stdout] duplicating out=%d to STDOUT\n", out);
		if (dup2(out, STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
		}
		dprintf(2, "[DEBUG setup_stdout] closing out=%d\n", out);
		close(out);
	}
}

