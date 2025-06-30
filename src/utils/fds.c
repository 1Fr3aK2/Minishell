/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:12 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:05:03 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	dup_and_close(int oldfd, int newfd, const char *errmsg)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror(errmsg);
		exit(1);
	}
	close(oldfd);
}

static void	handle_io_input(t_tree *node, int in)
{
	dup_and_close(node->io->fd_in, STDIN_FILENO, "dup2 node input");
	node->io->fd_in = -1;
	if (in != -1)
		close(in);
}

static void	handle_heredoc_case(t_tree *node, int in)
{
	if (in != -1)
		close(in);
	handle_heredoc(node);
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
