/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 02:55:31 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 19:09:10 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	setup_io_fds(in, out);
	process_redirections(node, info);
	if (info->exit_status == 258)
		exit(258);
	handle_node_io(node);
	execute_node(info, node);
	ft_exit2(info);
}

pid_t	handle_pipe_fork(t_info *info, t_tree *node, int in, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		close_pipe_fds(fd);
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

pid_t	create_pipe(t_info *info, t_tree *node, int in, int *out)
{
	int		fd[2];
	pid_t	pid;

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
	*out = fd[0];
	return (pid);
}

void	ft_pipe(t_info *info, t_tree *node)
{
	t_tree	*curr;
	pid_t	last_pid;
	int		in;

	curr = node;
	last_pid = -1;
	in = -1;
	handle_pipe_loop(info, &curr, &in, &last_pid);
	if (curr)
		handle_fork_exec(info, curr, in, &last_pid);
	if (in != -1 && info->in_redir == true)
		close(in);
	wait_all(last_pid, info);
	if (in != -1 && info->in_redir == false)
		close(in);
	close_heredoc_fds(info->cmd_tree);
}

void	ft_pipe_wrapper(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;
	if (check_pipeline_redirection(info->cmd_tree))
		info->in_redir = true;
	prepare_heredocs(info->cmd_tree, info);
	if (info->exit_status == 130)
		return ;
	ft_pipe(info, info->cmd_tree);
}
