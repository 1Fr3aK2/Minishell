/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/16 19:02:23 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_signals(void)
{
	//signal(SIGPIPE, handle_sigpipe);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_parent_signals(int status, t_info *info)
{
	if (WIFEXITED(status))
		update_status(info, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			update_status(info, 131);
			write(1, "Quit (core dumped)\n", 19);
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			update_status(info, 130);
			write(1, "\n", 1);
		}
	}
}

void	exec_child_process(t_info *info)
{
	handle_child_signals();
	if (info->io->heredoc_fd != -1)
	{
		dup2(info->io->heredoc_fd, STDIN_FILENO);
		close(info->io->heredoc_fd);
		info->io->heredoc_fd = -1;
	}
	else if (info->io->fd_in != -1)
	{
		dup2(info->io->fd_in, STDIN_FILENO);
		close(info->io->fd_in);
		info->io->fd_in = -1;
	}
	if (info->io->fd_out != -1)
	{
		dup2(info->io->fd_out, STDOUT_FILENO);
		close(info->io->fd_out);
		info->io->fd_out = -1;
	}
	exec(info, info->cmd_tree);
	exit(1);
}

void	handle_exec_failure(t_info *info, char *cmd, int exit_code)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	info->exit_status = exit_code;
	ft_exit2(info);
}

void	exec(t_info *info, t_tree *node)
{
	char	*path;

	if (!info)
		return ;
	restore_io(info->io);
	path = find_path(info, node->args[0]);
	if (!path)
		handle_exec_failure(info, node->args[0], 127);
	if (execve(path, node->args, info->my_env) == -1)
	{
		free(path);
		handle_exec_failure(info, node->args[0], 126);
	}
}
