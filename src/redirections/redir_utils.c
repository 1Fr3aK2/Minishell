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
	if (!io)
		return ;
	io->stdin_backup = dup(STDIN_FILENO);   // Backup stdin
	io->stdout_backup = dup(STDOUT_FILENO); // Backup stdout
	if (io->stdin_backup == -1 || io->stdout_backup == -1)
		error_exit("dup failed: Could not backup stdin or stdout");
}

/*
	Restores the original standard input and output
	to their original fds of 0 and 1.
*/
void	restore_io(t_io *io)
{
	if (!io)
		return ;
	if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
	// STDIN now points to whatever file is stored in backup (which is fd(0))
	{
		close(io->stdin_backup);
		close(io->stdout_backup);
		error_exit("dup2 failed: Could not restore STDIN");
	}
	if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
	{
		close(io->stdin_backup);
		close(io->stdout_backup);
		error_exit("dup2 failed: Could not restore STDOUT");
	}
	close(io->stdin_backup);
	close(io->stdout_backup);
}
