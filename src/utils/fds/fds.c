/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:12 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 04:36:41 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_node_io(t_tree *node)
{
	if (node->io && node->io->fd_in != -1)
		dup_and_close_fd(node->io->fd_in, STDIN_FILENO, "dup2 file stdin");
	else if (node->io && node->io->heredoc_fd != -1)
		dup_and_close_fd(node->io->heredoc_fd, STDIN_FILENO,
			"dup2 heredoc stdin");
	if (node->io && node->io->fd_out != -1)
		dup_and_close_fd(node->io->fd_out, STDOUT_FILENO, "dup2 file stdout");
}

void	close_heredoc_fds(t_tree *node)
{
	if (!node)
		return ;
	if (node->io && node->io->heredoc_fd != -1)
	{
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
	close_heredoc_fds(node->left);
	close_heredoc_fds(node->right);
}
