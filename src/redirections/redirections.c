/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/20 20:31:27 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	handle_output_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return ;
	if (io->fd_out > 2)
		close(io->fd_out);
	io->fd_out = open(io->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		ft_putstr_fd("open failed in fd_out\n", 2);
		info->exit_status = 1;
	}
}

void	handle_input_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return ;
	if (io->fd_in > 2)
		close(io->fd_in);
	io->fd_in = open(io->file, O_RDONLY);
	if (io->fd_in == -1)
	{
		ft_putstr_fd("open failed in fd_in\n", 2);
		info->exit_status = 1;
	}
}

void	handle_append_redirection(t_io *io, t_info *info)
{
	if (!io || !io->file)
		return ;
	if (io->fd_out > 2)
		close(io->fd_out);
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
	{
		ft_putstr_fd("open failed in fd_out\n", 2);
		info->exit_status = 1;
	}
}
