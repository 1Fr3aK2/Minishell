/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/05/06 19:16:19 by rafael           ###   ########.fr       */
=======
/*   Updated: 2025/04/23 17:38:51 by rafael           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	exec_command(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	info->cmd_tree = node;
<<<<<<< Updated upstream
	if (check_redirections(info) == 0)
		exit(0);
	if (check_operators(info) == 0)
		exit(0);
=======
	if (check_operators(info) == 0)
		exit(0);
	if (check_redirections(info) == 0)
		exit(0);
>>>>>>> Stashed changes
	if (check_builtins(info) == 0)
		exit(0);
	else if (node->type == CMD)
		exec(info, node);
<<<<<<< Updated upstream
	exit(127);
=======
	exit(1);
>>>>>>> Stashed changes
}

void ft_pipe(t_info *info, t_tree *node)
{
<<<<<<< Updated upstream
	int fd[2], prev_fd = -1;
	pid_t pid, last_pid = -1;
	t_tree *curr = node;

	while (curr && curr->type == PIPE)
	{
		if (pipe(fd) == -1)
			return (ft_putstr_fd("Pipe error\n", 2));
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("Fork error\n", 2));
		if (pid == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO), close(prev_fd);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]), close(fd[1]);
			exec_command(info, curr->left);
		}
		if (prev_fd != -1)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		curr = curr->right;
	}
	if (curr)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("Fork error\n", 2));
		if (pid == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO), close(prev_fd);
			exec_command(info, curr);
		}
		last_pid = pid;
	}
	if (prev_fd != -1)
		close(prev_fd);

	int status;
	pid_t wpid;
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (wpid == last_pid && WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				g_exit_status = 131, write(1, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				g_exit_status = 130, write(1, "\n", 1);
		}
	}
=======
    int fd[2], prev_fd = -1;
    pid_t pid;
    t_tree *curr = node;

    while (curr && curr->type == PIPE)
    {
        if (pipe(fd) == -1)
        {
            ft_putstr_fd("Pipe error", 2);
            return;
        }
        
        pid = fork();
        if (pid == -1)
        {
            ft_putstr_fd("Fork error", 2);
            return;
        }
        if (pid == 0) // Child process
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            exec_command(info, curr->left);
        }
        if (prev_fd != -1)
            close(prev_fd);
        close(fd[1]);
        prev_fd = fd[0];
        curr = curr->right;
    }
    // Last command in the pipe sequence
    if (curr)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_putstr_fd("Fork error", 2);
            return;
        }
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            exec_command(info, curr);
        }
    }
    if (prev_fd != -1)
        close(prev_fd);
    while (wait(NULL) > 0); // Wait for all child processes to complete
>>>>>>> Stashed changes
}

void	ft_pipe_wrapper(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;
	ft_pipe(info, info->cmd_tree);
}
