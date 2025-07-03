/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:57:12 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 04:05:09 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_and_close(int oldfd, int newfd, const char *errmsg)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror(errmsg);
		exit(1);
	}
	close(oldfd);
}

void	handle_io_input(t_tree *node, int in)
{
	dup_and_close(node->io->fd_in, STDIN_FILENO, "dup2 node input");
	node->io->fd_in = -1;
	if (in != -1)
		close(in);
}

void	handle_heredoc_case(t_tree *node, int in)
{
	if (in != -1)
		close(in);
	handle_heredoc(node);
}

void	restore_redirections(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}
