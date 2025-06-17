/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:44:02 by rafael            #+#    #+#             */
/*   Updated: 2025/06/17 20:08:52 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_all(pid_t last_pid, t_info *info)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			update_status(info, WEXITSTATUS(status));
		else if (wpid == last_pid && WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				update_status(info, 131);
				write(1, "Quit (core dumped)\n", 19);
			}
			else if (WTERMSIG(status) == SIGINT)
				update_status(info, 130);
		}
		wpid = wait(&status);
	}
}

void	dup_pipe_fds(int in, int out)
{
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
}

void	handle_heredoc(t_tree *node)
{
	if (node->io && node->io->heredoc_fd != -1)
	{
		dup2(node->io->heredoc_fd, STDIN_FILENO);
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
}

void	exec_command(t_info *info, t_tree *node)
{
	if (node->type == PIPE)
		ft_pipe(info, node);
	else if (node->type == AND)
		ft_and(info, node);
	else if (node->type == OR)
		ft_or(info, node);
	else
		exit(127);
	close_fds(0);
	exit(info->exit_status);
}
