/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (!io)
		return ;
	close_and_reset(&io->heredoc_fd);
	if (io->stdin_backup != -1)
	{
		dup2(io->stdin_backup, STDIN_FILENO);
		close_and_reset(&io->stdin_backup);
	}
	if (io->stdout_backup != -1)
	{
		dup2(io->stdout_backup, STDOUT_FILENO);
		close_and_reset(&io->stdout_backup);
	}
	close_and_reset(&io->fd_in);
	close_and_reset(&io->fd_out);
	io->stdin_is_heredoc = 0;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close_fds(0);
	exit(130);
}
