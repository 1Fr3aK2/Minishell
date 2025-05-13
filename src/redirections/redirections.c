/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/13 19:34:14 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	handle_output_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_out = open(io->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		ft_putstr_fd("open failed in fd_out", 2);
	}
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed in output redirection", 2);
	}
	close(io->fd_out);
}

void	handle_input_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_in = open(io->file, O_RDONLY);
	if (io->fd_in == -1)
	{
		ft_putstr_fd("open failed in fd_in", 2);
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (dup2(io->fd_in, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed in input redirection", 2);
		close(io->fd_in);
		io->fd_in = -1;
	}
	close(io->fd_in);
}

void	handle_append_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
	{
		ft_putstr_fd("open failed in fd_out", 2);
		close(io->fd_out);
		io->fd_out = -1;
	}
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed in output redirection", 2);
		close(io->fd_out);
		io->fd_out = -1;
	}
	close(io->fd_out);
}
