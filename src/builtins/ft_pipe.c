/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/19 19:31:54 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void exec_command(t_info *info, t_tree *node)
{
    if (!info || !node)
        return;
    info->cmd_tree = node;
    if (check_builtins(info) == 0)
        exit(0);
    exec(info);
    ft_putstr_fd("Exec error", 2);
}

void ft_pipe(t_info *info, t_tree *node)
{
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (!info || !node || !node->left || !node->right)
        return;
    if (pipe(fd) == -1)
        return(ft_putstr_fd("Pipe error", 2));
    if (check_builtins(info) == 0)
        return;
    pid1 = fork();
    if (pid1 == -1)
        return (ft_putstr_fd("Fork error", 2));
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        exec_command(info, node->left);
    }
    pid2 = fork();
    if (pid2 == -1)
        return (ft_putstr_fd("Fork error", 2));
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        exec_command(info, node->right);
    }
    close_pipe_fds(fd);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void ft_pipe_wrapper(t_info *info)
{
    if (!info || !info->cmd_tree)
        return;
    ft_pipe(info, info->cmd_tree);
}
