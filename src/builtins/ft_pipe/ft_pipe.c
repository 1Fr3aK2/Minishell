/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 02:55:31 by rafael            #+#    #+#             */
/*   Updated: 2025/06/28 16:01:20 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	dprintf(2, "[DEBUG child_exec] PID=%d in=%d out=%d\n", getpid(), in, out);
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

	dprintf(2, "[DEBUG handle_pipe_fork] before fork - in=%d fd[0]=%d fd[1]=%d\n", in, fd[0], fd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		dprintf(2, "[DEBUG handle_pipe_fork - CHILD] PID=%d closing fd[0]=%d\n", getpid(), fd[0]);
		close(fd[0]);
		child_exec(info, node->left, in, fd[1]);
	}
	dprintf(2, "[DEBUG handle_pipe_fork - PARENT] PID=%d closing fd[1]=%d (child PID=%d)\n", getpid(), fd[1], pid);
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

	dprintf(2, "DEBUG: create_pipe() called with in=%d, has_heredoc=%d\n", in, has_heredoc);

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return (-1);
	}

	dprintf(2, "DEBUG: pipe created: fd[0]=%d (read end), fd[1]=%d (write end)\n", fd[0], fd[1]);

	pid = handle_pipe_fork(info, node, in, fd);

	if (pid == -1)
	{
		dprintf(2, "DEBUG: handle_pipe_fork() returned error\n");
		return (-1);
	}

	dprintf(2, "DEBUG: handle_pipe_fork() returned pid=%d\n", pid);

	if (in != -1)
	{
		dprintf(2, "DEBUG: closing previous input fd=%d\n", in);
		close(in);
	}

	if (has_heredoc)
	{
		*out = fd[0];
		dprintf(2, "DEBUG: has_heredoc=1, setting *out to fd[0]=%d\n", fd[0]);
	}
	else
	{
		*out = fd[0];
		dprintf(2, "DEBUG: has_heredoc=0, setting *out to fd[0]=%d\n", fd[0]);
	}

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
	dprintf(2, "[DEBUG ft_pipe] entering pipe loop\n");
	while (curr && curr->type == PIPE)
	{
		dprintf(2, "[DEBUG ft_pipe] create_pipe for node at %p\n", (void*)curr);
		pid = create_pipe(info, curr, in, &in);
		if (pid == -1)
		{
			dprintf(2, "[DEBUG ft_pipe] create_pipe failed, returning\n");
			return ;
		}
		curr = curr->right;
	}
	if (curr)
	{
		dprintf(2, "[DEBUG ft_pipe] final fork for last command\n");
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			if (in != -1) close(in);
			return ;
		}
		if (pid == 0)
			child_exec(info, curr, in, -1);
	}
	wait_all(pid, info);
	if (in != -1)
	{
		dprintf(2, "[DEBUG ft_pipe] closing last in=%d\n", in);
		close(in);
	}
	dprintf(2, "[DEBUG ft_pipe] closing heredocs\n");
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
	/* close_heredoc_fds(info->cmd_tree); */
}
