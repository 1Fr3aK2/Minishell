/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/24 17:54:30 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void    handle_input_redirection(t_io *io, char *infile)
{
    if (!io && !infile)
        return ;
    io->fd_in = open(infile, O_RDONLY);
    if (io->fd_in == -1)
        error_exit("open failed in fd_in");
    if (dup2(io->fd_in, STDIN_FILENO) == -1)
    {
        close(io->fd_in);
        error_exit("dup2 failed: Could not redirect STDIN");
    }
    close(io->fd_in);
}

void    handle_output_redirection(t_io *io, char *outfile)
{
    if (!io && !outfile)
        return ;
    io->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // O_TRUNC will overwritten the content
    if (io->fd_out == -1)
        error_exit("open failed in fd_out");
    if (dup2(io->fd_out, STDOUT_FILENO) == -1)
    {
        close(io->fd_out);
        error_exit("dup2 failed: Could not redirect STDOUT");
    }
    close(io->fd_out);
}

void    handle_append_redirection(t_io *io, char *outfile)
{
    if (!io && !outfile)
        return ;
    io->fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (io->fd_out == -1)
        error_exit("open failed in fd_out append");
    if (dup2(io->fd_out, STDOUT_FILENO) == -1)
    {
        close(io->fd_out);
        error_exit("dup2 failed: Could not redirect STDOUT append");
    }
    close (io->fd_out);
}

void    handle_heredoc_redirection(t_io *io, char *delimiter)
{
    char    *line;
    int     pipe_fd[2];

    if (!io || !delimiter)
        return ;
    if (pipe(pipe_fd) == -1)
        error_exit("pipe failed for heredoc");
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        close(pipe_fd[0]);
        error_exit("dup2 failed: Could not redirect STDIN heredoc");
    }
    close(pipe_fd[0]);
}

void handle_redirections(t_io *io, char **args)
{
    int i = 0;
    while (args[i])
    {
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1])
            {
                handle_output_redirection(io, args[i + 1]);
                i++; // Skip the next argument as it's the filename
            }
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1])
            {
                handle_append_redirection(io, args[i + 1]);
                i++;
            }
        }
        else if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1])
            {
                handle_input_redirection(io, args[i + 1]);
                i++;
            }
        }
        else if (strcmp(args[i], "<<") == 0)
        {
            if (args[i + 1])
            {
                handle_heredoc_redirection(io, args[i + 1]);
                i++;
            }
        }
        i++;
    }
}
