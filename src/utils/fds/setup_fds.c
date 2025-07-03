/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 03:55:37 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 04:21:32 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setup_io_fds(int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
		dup_and_close_fd(in, STDIN_FILENO, "dup2 stdin");
	if (out != -1 && out != STDOUT_FILENO)
		dup_and_close_fd(out, STDOUT_FILENO, "dup2 stdout");
}

void	setup_io_from_tree(t_info *info)
{
	if (info->cmd_tree && info->cmd_tree->io)
	{
		if (info->io->heredoc_fd != -1)
			close(info->io->heredoc_fd);
		info->io->heredoc_fd = info->cmd_tree->io->heredoc_fd;
		info->cmd_tree->io->heredoc_fd = -1;
		info->io->stdin_is_heredoc = info->cmd_tree->io->stdin_is_heredoc;
	}
}
