/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/20 16:19:01 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	if (info->io && info->io->fd_in != -1)
	{
		dup2(info->io->fd_in, STDIN_FILENO);
		close(info->io->fd_in);
		info->io->fd_in = -1;
	}
	else if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	close_fds(0);
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
		return (ft_putstr_fd("Fork error\n", 2), -1);
	if (pid == 0)
		child_exec(info, node->left, in, fd[1]);
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
	if (info->io && info->io->heredoc_fd != -1)
	{
		in = info->io->heredoc_fd;
		info->io->heredoc_fd = -1;
	}
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
}
