/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:01:40 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/11 17:17:16 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc_child(t_io *io, t_info *info, int fd[2])
{
	signal(SIGINT, handle_sigint_heredoc);
	close(fd[0]);
	close_heredoc_backups(io);
	heredoc_loop(io, info, fd);
	close(fd[1]);
	ft_exit2(info);
}

void	handle_heredoc_parent(t_io *io, t_info *info, int fd[2], pid_t pid)
{
	int	status;

	(void)status;
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		update_status(info, 130);
		close(fd[0]);
		restore_io(io);
		return ;
	}
	if (io->fd_in != -1)
		close(io->fd_in);
	io->heredoc_fd = fd[0];
	io->stdin_is_heredoc = 1;
}

void	handle_heredoc_redirection(t_io *io, t_info *info)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	(void)status;
	if (!io || !io->file || pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return (close_pipe_fds(fd), (void)0);
	if (pid == 0)
		handle_heredoc_child(io, info, fd);
	else
		handle_heredoc_parent(io, info, fd, pid);
}

int	process_heredoc_args(t_tree *node, t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (node->args[i])
	{
		if (ft_strncmp(node->args[i], "<<", 2) == 0 && node->args[i][2] == '\0')
		{
			if (!node->args[i + 1])
				return (info->exit_status = 2, -1);
			status = setup_heredoc_io(node, info, i);
			if (status == -1)
				return (-1);
			remove_redir_tokens(node->args, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	prepare_heredocs(t_tree *node, t_info *info)
{
	if (!node)
		return ;
	if (node->type == CMD && node->args)
		process_heredoc_args(node, info);
	prepare_heredocs(node->left, info);
	prepare_heredocs(node->right, info);
}
