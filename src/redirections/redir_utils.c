/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/27 17:13:59 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	storing_backup(t_io *io)
{
	io->stdin_backup = dup(STDIN_FILENO);
	io->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_io(t_io *io)
{
	dup2(io->stdin_backup, STDIN_FILENO);
	dup2(io->stdout_backup, STDOUT_FILENO);
	close(io->stdin_backup);
	close(io->stdout_backup);
	if (io->fd_in > 0)
		close(io->fd_in);
	if (io->fd_out > 0)
		close(io->fd_out);
}
