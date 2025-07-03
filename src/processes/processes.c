/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/03 03:43:20 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (exit_code == 127)
	{
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
	}
	else if (exit_code == 126)
	{
		if (is_directory(cmd))
			ft_putstr_fd(": Is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	info->exit_status = exit_code;
	ft_exit2(info);
}

void	exec(t_info *info, t_tree *node)
{
	char	*path;

	if (!info || !node || !node->args || !node->args[0])
		return ;
	restore_io(info->io);
	path = find_path(info, node->args[0]);
	if (!path)
	{
		if (ft_strchr(node->args[0], '/'))
			errno = ENOENT;
		else
			errno = 0;
		handle_exec_failure(info, node->args[0], 127);
	}
	if (is_directory(path))
	{
		free(path);
		handle_exec_failure(info, node->args[0], 126);
	}
	if (execve(path, node->args, info->my_env) == -1)
	{
		free(path);
		handle_exec_failure(info, node->args[0], 126);
	}
}
