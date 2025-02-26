/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:48 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 16:35:09 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// ver HEREDOC

void	fill_redirections(t_io *io)
{
    if (!io)
        return;
    io->redirections = malloc(sizeof(t_reds));
    if (!io->redirections)
    {
        error_exit("Memory allocation failed for redirections");
    }
	io->redirections->reds[0] = ">";
	io->redirections->reds[1] = "<";
	io->redirections->reds[2] = ">>";
	io->redirections->reds[3] = "<<";
	io->redirections->reds[4] = NULL;
    io->redirections->f[0] = handle_output_redirection; // >
    io->redirections->f[1] = handle_input_redirection;  // <
    io->redirections->f[2] = handle_append_redirection; // >>
    io->redirections->f[3] = handle_heredoc_redirection; // <<
    io->redirections->f[4] = NULL;
}

void    handle_input_redirection(t_io *io)
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

void    handle_output_redirection(t_io *io)
{
    if (!io && !io->out_file)
        return ;
    io->fd_out = open(io->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // O_TRUNC will overwritten the content
    if (io->fd_out == -1)
        error_exit("open failed in fd_out");
    if (dup2(io->fd_out, STDOUT_FILENO) == -1)
    {
        close(io->fd_out);
        error_exit("dup2 failed: Could not redirect STDOUT");
    }
    close(io->fd_out);
}

void    handle_append_redirection(t_io *io)
{
    if (!io && !io->out_file)
        return ;
    io->fd_out = open(io->out_file, O_WRONLY | O_CREAT | O_APPEND);
    if (io->fd_out == -1)
        error_exit("open failed in fd_out append");
    if (dup2(io->fd_out, STDOUT_FILENO) == -1)
    {
        close(io->fd_out);
        error_exit("dup2 failed: Could not redirect STDOUT append");
    }
    close (io->fd_out);
}

void    handle_heredoc_redirection(t_io *io)
{
    if (!io && !io->in_file)
        return ;
    io->fd_in = open(io->in_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (io->fd_in == -1)
        error_exit("open failed in fd_in heredoc");
    if (dup2(io->fd_in, STDIN_FILENO) == -1)
    {
        close(io->fd_in);
        error_exit("dup2 failed: Could not redirect STDIN heredoc");
    }
    close(io->fd_in);

}

void    heredoc_prompt(t_info *info)
{
    int i;

    i = 0;
    if (info->args[i] == "EOF")
    {
        printf(">");
    }
}
/*
    Backs up the standard input and output before replacing them, in order
    to restore them after execution.
    dup() will create a copy of the file descriptor STDIN_FILENO (0), 
    and store it in the lowest available file descriptor, which, if no other file descriptors are open, will be 3.
    So, stdin_backup will now hold the value 3, 
    and it points to the same file/stream as STDIN_FILENO, but it’s a separate descriptor.
*/
void    storing_backup(t_io *io)
{
    if (io)
    {
        io->stdin_backup = dup(STDIN_FILENO); // the backup points to fd(0)
        io->stdout_backup = dup(STDOUT_FILENO); // the backup points to fd(1)
        if (io->stdin_backup == -1 || io->stdout_backup == -1)
            error_exit("dup failed: Could not backup stdin or stdout");
        //handle_input_redirection(io);
        //handle_output_redirection(io); // after the duplications are done, we can finally redirect stuff
        handle_append_redirection(io);
    }
}

/*
    Restores the original standard input and output
    to their original fds of 0 and 1. Used to clear the input/output
    fds after execution, in preparation for the next set of user commands.
*/
void restore_io(t_io *io)
{
    if (io)
    {
        if (dup2(io->stdin_backup, STDIN_FILENO) == -1) // STDIN now points to whatever file is stored in backup (which is fd(0))
        {
            close(io->stdin_backup);
            close(io->stdout_backup);
            error_exit("dup2 failed: Could not restore STDIN");
        }
        if (dup2(io->stdout_backup, STDOUT_FILENO) == -1) 
        {
            close(io->stdin_backup);
            close(io->stdout_backup);
            error_exit("dup2 failed: Could not restore STDOUT");
        }
        close(io->stdin_backup);
        close(io->stdout_backup);
    }
}

// so pra testar
// works for output, not for input
void execute_command(t_info *info)
{
    int i;

    i = 0;
    while (info->args[i] != NULL)
    {
        if (ft_strncmp(info->args[i], ">>", 2) == 0)
        {
            info->io.out_file = info->args[i + 1]; // the next arg after ">" is the output file name
            info->args[i] = NULL; // this is necessary for execvp to work
            break;
        }
        i++;
    }
    storing_backup(&info->io);
    handle_append_redirection(&info->io);
    if (info->args[0] != NULL)
    {
        if (execvp(info->args[0], info->args) == -1)
        {
            error_exit("execvp failed");
        }
    }
    restore_io(&info->io);
}


/*
Right now, if execvp() works, your shell gets replaced by the new process.
This is the reason the terminal leaves shellinho after execution of a redirection
Use fork() like this:

pid_t pid = fork();
if (pid == -1)
    error_exit("fork failed");

if (pid == 0) // Child process
{
    storing_backup(&info->io);
    handle_output_redirection(&info->io);
    execvp(info->args[0], info->args);
    error_exit("execvp failed"); // Only runs if execvp fails
}
else // Parent process
{
    waitpid(pid, NULL, 0); // Wait for child to finish
    restore_io(&info->io);
}
*/