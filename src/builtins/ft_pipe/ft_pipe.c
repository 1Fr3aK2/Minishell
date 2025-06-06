/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/06 16:04:41 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (node->io && node->io->heredoc_fd != -1)
	{
		dup2(node->io->heredoc_fd, STDIN_FILENO);
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
	else if (node->io && node->io->fd_in != -1)
	{
		dup2(node->io->fd_in, STDIN_FILENO);
		close(node->io->fd_in);
		node->io->fd_in = -1;
	}
	else if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	//signal(SIGPIPE, handle_sigpipe);
	exec_command_op(info, node);
	ft_exit2(info);
}

static pid_t	handle_pipe_fork(t_info *info, t_tree *node, int in, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (close_pipe_fds(fd), -1);
	if (pid == 0)
	{
		close(fd[0]);
		child_exec(info, node->left, in, fd[1]);
	}
	if (in != -1)
		close(in);
	close(fd[1]);
	return (pid);
}

static pid_t	create_pipe(t_info *info, t_tree *node, int in, int *out)
{
	int		fd[2];
	pid_t	pid;
	int		has_heredoc;

	has_heredoc = node->right && node->right->io
		&& node->right->io->heredoc_fd != -1;
	if (pipe(fd) == -1)
		return (ft_putstr_fd("Pipe error\n", 2), -1);
	pid = handle_pipe_fork(info, node, in, fd);
	if (pid == -1)
		return (-1);
	if (has_heredoc)
	{
		close(fd[0]);
		*out = -1;
	}
	else
		*out = fd[0];
	return (pid);
}

void	ft_pipe(t_info *info, t_tree *node)
{
	t_tree	*curr;
	pid_t	pid;
	int		in;

	curr = node;
	pid = -1;
	in = -1;
	while (curr && curr->type == PIPE)
	{
		pid = create_pipe(info, curr, in, &in);
		if (pid == -1)
			return ;
		curr = curr->right;
	}
	if (curr)
	{
		pid = fork();
		if (pid == 0)
			child_exec(info, curr, in, -1);
	}
	if (in != -1)
		close(in);
	wait_all(pid, info);
}

void	ft_pipe_wrapper(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;
	prepare_heredocs(info->cmd_tree, info);
	if (info->exit_status == 130)
		return ;
	ft_pipe(info, info->cmd_tree);
	close_heredoc_fds(info->cmd_tree);
}
