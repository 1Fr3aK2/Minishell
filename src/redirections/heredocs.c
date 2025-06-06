/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:01:40 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/05 22:33:25 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	child_heredoc_writer(t_io *io, t_info *info, int write_fd)
{
	char	*line;
	char	*temp;

	signal(SIGINT, handle_sigint_heredoc);
	close_and_reset(&io->stdin_backup);
	close_and_reset(&io->stdout_backup);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
				&& ft_strlen(line) == ft_strlen(io->file)))
		{
			free(line);
			break ;
		}
		temp = handle_dollar(line, info);
		if (!temp)
			temp = ft_strdup("");
		write(write_fd, temp, ft_strlen(temp));
		write(write_fd, "\n", 1);
		free(line);
		free(temp);
	}
	close(write_fd);
	exit(0);
}

static int	parent_heredoc_handler(t_io *io, t_info *info, int fd_read, int pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd_read + 1);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		update_status(info, 130);
		close(fd_read);
		restore_io(io);
		return (1);
	}
	if (io->fd_in != -1)
		close(io->fd_in);
	io->heredoc_fd = fd_read;
	io->stdin_is_heredoc = 1;
	return (0);
}

void	handle_heredoc_redirection(t_io *io, t_info *info)
{
	int		fd[2];
	pid_t	pid;

	if (!io || !io->file || pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
	{
		close_pipe_fds(fd);
		return ;
	}
	if (pid == 0)
		child_heredoc_writer(io, info, fd[1]);
	else
		parent_heredoc_handler(io, info, fd[0], pid);
}

int	process_heredoc_args(t_tree *node, t_info *info)
{
	int	i;

	i = 0;
	while (node->args[i])
	{
		if (ft_strncmp(node->args[i], "<<", 2) == 0 && node->args[i][2] == '\0')
		{
			if (!node->args[i + 1])
				return (info->exit_status = 2, -1);
			if (!node->io)
			{
				node->io = malloc(sizeof(t_io));
				if (!node->io)
					return (-1);
				init_io(node->io);
			}
			update_io_file(node->io, node->args[i + 1]);
			handle_heredoc_redirection(node->io, info);
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
