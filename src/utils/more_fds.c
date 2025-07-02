/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:49:01 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:50:25 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_and_close_fd(int fd, int std_fd, const char *err_msg)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror(err_msg);
		exit(1);
	}
	close(fd);
}

void	setup_io_fds(int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
		dup_and_close_fd(in, STDIN_FILENO, "dup2 stdin");
	if (out != -1 && out != STDOUT_FILENO)
		dup_and_close_fd(out, STDOUT_FILENO, "dup2 stdout");
}

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

void	cleanup_and_exit(t_info *info)
{
	info->exit_status = 0;
	ft_exit(info);
}
