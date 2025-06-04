/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:01:40 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/04 17:10:12 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	handle_heredoc_redirection(t_io *io, t_info *info)
{
	char	*line;
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!io || !io->file)
	{
		printf("Debug: io or io->file is NULL\n");
		return ;
	}
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		close(fd[0]);
		if (io->stdin_backup != -1)
		{
			close(io->stdin_backup);
			io->stdin_backup = -1;
		}
		if (io->stdout_backup != -1)
		{
			close(io->stdout_backup);
			io->stdout_backup = -1;
		}
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
					&& ft_strlen(line) == ft_strlen(io->file)))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
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
			{
				info->exit_status = 2;
				return (-1);
			}
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
