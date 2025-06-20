/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/20 16:40:14 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* static void	handle_child_process(t_info *info, t_tree *node)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		dup2(info->io->fd_in, STDIN_FILENO);
		close(info->io->fd_in);
	}
	exec_command(info, node);
} */
static void	close_heredoc_fd(t_info *info)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		close(info->io->fd_in);
		info->io->fd_in = -1;
		info->io->stdin_is_heredoc = 0;
	}
}
/*
static void	handle_status(t_info *info, int status)
{
	int	sig;

	if (WIFEXITED(status))
		update_status(info, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			update_status(info, 130);
		else if (sig == SIGQUIT)
		{
			update_status(info, 131);
			write(1, "Quit (core dumped)\n", 19);
		}
	}
} */

void	exec_command_op(t_info *info, t_tree *node)
{
	if (check_builtins(info) == 0)
	{
		close_heredoc_fd(info);
		close_fds(0);
		exit(info->exit_status);
	}
	exec(info, node);
	close_heredoc_fd(info);
	close_fds(0);
	exit(info->exit_status);
}
