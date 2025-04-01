/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/27 17:32:18 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// TO DO = parse the in_file and out_file
/*
Nota: o dup2 e necessario pra duplicar o fd, porque,
no caso do STDOUT, por exemplo, queremos redirecionar
o output pra um ficheiro outfile.txt, inves do terminal.
*/ 
void	handle_input_redirection(t_io *io)
{
	if (!io && !io->in_file)
		return ;
	io->fd_in = open(io->in_file, O_RDONLY);
	if (io->fd_in == -1)
		error_exit("open failed in fd_in");
	if (dup2(io->fd_in, STDIN_FILENO) == -1)
	{
		close(io->fd_in);
		error_exit("dup2 failed: Could not redirect STDIN");
	}
	close(io->fd_in);
}

void	handle_output_redirection(t_io *io)
{
	if (!io && !io->out_file)
		return ;
	io->fd_out = open(io->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io->fd_out == -1)
		error_exit("open failed in fd_out");
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
	{
		close(io->fd_out);
		error_exit("dup2 failed: Could not redirect STDOUT");
	}
	close(io->fd_out);
}

void	handle_append_redirection(t_io *io)
{
	if (!io && !io->out_file)
		return ;
	io->fd_out = open(io->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
		error_exit("open failed in fd_out append");
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
	{
		close(io->fd_out);
		error_exit("dup2 failed: Could not redirect STDOUT append");
	}
	close(io->fd_out);
}

void	handle_heredoc_redirection(t_io *io)
{
	char	*line;
	int		fd[2];

	if (!io || !io->here_delimiter)
		return ;
	if (pipe(fd) == -1)
		error_exit("pipe failed for heredoc");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, io->here_delimiter,
				ft_strlen(io->here_delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
    }
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		error_exit("dup2 failed: Could not redirect heredoc");
	}
	close(fd[0]);
}

void	handle_redirections(t_io *io, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">") == 0)
		{
			if (args[i + 1])
			{
				handle_output_redirection(io);
				i++; // Skip the next argument as it's the filename
			}
		}
		else if (strcmp(args[i], ">>") == 0)
		{
			if (args[i + 1])
			{
				handle_append_redirection(io);
				i++;
			}
		}
		else if (strcmp(args[i], "<") == 0)
		{
			if (args[i + 1])
			{
				handle_input_redirection(io);
				i++;
			}
		}
		else if (strcmp(args[i], "<<") == 0)
		{
			if (args[i + 1])
			{
				handle_heredoc_redirection(io);
				i++;
			}
		}
		i++;
	}
}
