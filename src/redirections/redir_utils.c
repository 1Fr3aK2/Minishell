/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/20 15:45:25 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	storing_backup(t_io *io)
{
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ft_putstr_fd("dup stdin backup failed", 2);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ft_putstr_fd("dup stdout backup failed", 2);
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
	if (io->fd_in > 2)
	{
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (io->fd_out > 2)
	{
		close(io->fd_out);
		io->fd_out = -1;
	}
	io->stdin_is_heredoc = 0;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close_fds(0);
	exit(130);
}
