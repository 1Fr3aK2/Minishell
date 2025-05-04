/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/23 15:20:24 by dsteiger         ###   ########.fr       */
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
	char				*line;
	int					fd[2];
	pid_t				pid;
	int					status;
	struct sigaction	original_sigint;

	if (!io || !io->file || pipe(fd) == -1)
		return ;
	// Save original SIGINT handler
	sigaction(SIGINT, NULL, &original_sigint);
	
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
        signal(SIGINT, SIG_DFL);
		// Child process
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
					&& ft_strlen(line) == ft_strlen(io->file)))
			{
				free(line);
				break ;
			}
			if (write(fd[1], line, ft_strlen(line)) == -1)
				break ;
			if (line[0] != '\0')
				write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
        // Parent process
		signal(SIGINT, SIG_IGN);
		close(fd[1]);

        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            write(1, "\n", 1);
        // Restore SIGINT handler (to your shell handler)
        signal(SIGINT, handle_sigint);
		// Restore original signal handler
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close(fd[0]);
			return ;
		}
		close(fd[0]);
	}
}
