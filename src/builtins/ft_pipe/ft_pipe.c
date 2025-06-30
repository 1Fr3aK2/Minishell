/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 02:55:31 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:37:30 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	if (in != -1 && in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(1);
		}
		close(in);
	}
	if (out != -1 && out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
		}
		close(out);
	}
	process_redirections(node, info);
	if (info->exit_status == 258)
		exit(258);
	if (node->io && node->io->fd_in != -1)
	{
		if (dup2(node->io->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 file stdin");
			exit(1);
		}
		close(node->io->fd_in);
	}
	else if (node->io && node->io->heredoc_fd != -1)
	{
		if (dup2(node->io->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc stdin");
			exit(1);
		}
		close(node->io->heredoc_fd);
	}
	if (node->io && node->io->fd_out != -1)
	{
		if (dup2(node->io->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 file stdout");
			exit(1);
		}
		close(node->io->fd_out);
	}
	execute_node(info, node);
	ft_exit2(info);
}

static pid_t	handle_pipe_fork(t_info *info, t_tree *node, int in, int *fd)
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

static pid_t	create_pipe(t_info *info, t_tree *node, int in, int *out)
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

	in = -1;
	curr = node;
	last_pid = -1;
	while (curr && curr->type == PIPE)
	{
		last_pid = create_pipe(info, curr, in, &in);
		if (last_pid == -1)
		{
			if (in != -1)
				close(in);
			return ;
		}
		curr = curr->right;
	}
	if (curr)
	{
		last_pid = fork();
		if (last_pid == -1)
		{
			perror("fork error");
			if (in != -1)
				close(in);
			return ;
		}
		if (last_pid == 0)
			child_exec(info, curr, in, -1);
	}
	if (in != -1 && info->in_redir == true)
		close(in);
	wait_all(last_pid, info);
	if (in != -1 && info->in_redir == false)
		close(in);
	close_heredoc_fds(info->cmd_tree);
}

bool	has_redirection(t_tree *node)
{
	int	i;

	if (!node || !node->args)
		return (false);
	i = 0;
	while (node->args[i])
	{
		if (ft_strncmp(node->args[i], "<", 2) == 0 || ft_strncmp(node->args[i],
				">", 2) == 0 || ft_strncmp(node->args[i], ">>", 3) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_pipeline_redirection(t_tree *node)
{
	if (!node)
		return (false);
	if (node->type == PIPE)
	{
		if (has_redirection(node->left))
			return (true);
		return (check_pipeline_redirection(node->right));
	}
	else if (node->type == CMD)
		return (has_redirection(node));
	return (false);
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
