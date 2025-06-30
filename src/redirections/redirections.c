/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/30 18:15:04 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_output_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (-1);
	if (io->fd_out != -1)
		close(io->fd_out);
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		perror("open output file");
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_append_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (-1);
	if (io->fd_out != -1)
		close(io->fd_out);
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
	{
		perror("open append file");
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	handle_input_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return (-1);
	if (io->fd_in != -1)
		close(io->fd_in);
	io->fd_in = open(io->file, O_RDONLY);
	if (io->fd_in == -1)
	{
		perror("open input file");
		info->exit_status = 1;
		return (-1);
	}
	return (0);
}


