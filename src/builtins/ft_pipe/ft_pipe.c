/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 02:55:31 by rafael            #+#    #+#             */
/*   Updated: 2025/06/28 02:57:07 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	setup_stdout(out);
	if (check_redirections_node(node, info) == 0)
		ft_exit2(info);
	setup_stdin(node, in);
	execute_node(info, node);
	ft_exit2(info);
}

static pid_t	handle_pipe_fork(t_info *info, t_tree *node, int in, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		child_exec(info, node->left, in, fd[1]);
	}
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
	{
		ft_putstr_fd("Pipe error\n", 2);
		return (-1);
	}
	pid = handle_pipe_fork(info, node, in, fd);
	if (pid == -1)
		return (-1);
	if (in != -1)
		close(in);
	if (has_heredoc)
		*out = fd[0];
	else
		*out = fd[0];
	return (pid);
}

void	ft_pipe(t_info *info, t_tree *node)
{
	t_tree	*curr;
	pid_t	pid;
	int		in;

	in = -1;
	curr = node;
	pid = -1;
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
	wait_all(pid, info);
	if (in != -1)
		close(in);
	close_heredoc_fds(info->cmd_tree);
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
