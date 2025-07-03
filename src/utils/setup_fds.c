/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 03:55:37 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 03:58:47 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_io_fds(int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
		dup_and_close_fd(in, STDIN_FILENO, "dup2 stdin");
	if (out != -1 && out != STDOUT_FILENO)
		dup_and_close_fd(out, STDOUT_FILENO, "dup2 stdout");
}

void	setup_stdin(t_tree *node, int in)
{
	if (node->io && node->io->fd_in != -1)
		handle_io_input(node, in);
	else if (node->io && node->io->heredoc_fd != -1)
		handle_heredoc_case(node, in);
	else if (in != -1)
	{
		dup_and_close(in, STDIN_FILENO, "dup2 stdin");
	}
}

void	setup_stdout(int out)
{
	if (out != -1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
		}
		close(out);
	}
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
