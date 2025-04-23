/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/23 15:19:19 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	storing_backup(t_io *io)
{
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		error_exit("dup stdin backup failed");
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		error_exit("dup stdout backup failed");
}

void	restore_io(t_io *io)
{
	if (io->stdin_backup != -1)
	{
		dup2(io->stdin_backup, STDIN_FILENO);
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		dup2(io->stdout_backup, STDOUT_FILENO);
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	if (io->fd_in > 0)
	{
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (io->fd_out > 0)
	{
		close(io->fd_out);
		io->fd_out = -1;
	}
}
