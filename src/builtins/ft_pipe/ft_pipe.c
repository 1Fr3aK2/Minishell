/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/05 03:00:45 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

static void	close_heredoc_fds(t_tree *node)
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
	/* close_fds(0); */
	exec_command(info, node);
	exit(1);
}

static pid_t	create_pipe(t_info *info, t_tree *node, int in, int *out)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_putstr_fd("Pipe error\n", 2), -1);
	pid = fork();
	if (pid == -1)
	{
		close_pipe_fds(fd);
		return (ft_putstr_fd("Fork error\n", 2), -1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		child_exec(info, node->left, in, fd[1]);
	}
	if (in != -1)
		close(in);
	close(fd[1]);
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
