/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/13 17:32:56 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	handle_output_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_out = open(io->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (io->fd_out == -1)
		error_exit("open failed in fd_out");
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		error_exit("dup2 failed in output redirection");
	close(io->fd_out);
}

void	handle_input_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_in = open(io->file, O_RDONLY);
	if (io->fd_in == -1)
		error_exit("open failed in fd_in");
	if (dup2(io->fd_in, STDIN_FILENO) == -1)
		error_exit("dup2 failed in input redirection");
	close(io->fd_in);
}

void	handle_append_redirection(t_io *io)
{
	if (!io || !io->file)
		return ;
	io->fd_out = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
		error_exit("open failed in fd_out append");
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		error_exit("dup2 failed in append redirection");
	close(io->fd_out);
}

void	handle_heredoc_redirection(t_io *io)
{
	char	*line;
	int		fd[2];
	pid_t	pid;
	int		status;
	int		tty_fd;

	if (!io || !io->file || pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd == -1)
			exit(1);
		while (1)
		{
			dup2(tty_fd, STDIN_FILENO);
			line = readline("> ");
			if (!line || (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
					&& ft_strlen(line) == ft_strlen(io->file)))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			if (line[0] != '\0')
				write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		close(tty_fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		close(fd[1]);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			g_exit_status = 130;
			close(fd[0]);
			return ;
		}
		signal(SIGINT, handle_sigint);
		if (dup2(fd[0], STDIN_FILENO) == -1) // Redirect stdin to the pipe
		{
			close(fd[0]);
			return ;
		}
	}
}

void prepare_heredocs(t_tree *node, t_info *info)
{
	int i;

	if (!node)
		return;

	if (node->type == CMD && node->args)
	{
		i = 0;
		while (node->args[i])
		{
			if (ft_strncmp(node->args[i], "<<", 2) == 0)
			{
				if (!node->args[i + 1])
				{
					ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
					g_exit_status = 2;
					return;
				}
				// Set up the heredoc target filename
				update_io_file(info->io, node->args[i + 1]);

				// Handle heredoc (this will fork, wait, and prepare the input)
				handle_heredoc_redirection(info->io);

				// Optional: remove the "<< delimiter" tokens from args[] here
				// so it doesn’t get re-parsed or mis-executed later
				remove_redir_tokens(node->args, i);
				i = -1; // Restart parsing since we removed args
			}
			i++;
		}
	}
	prepare_heredocs(node->left, info);
	prepare_heredocs(node->right, info);
}

