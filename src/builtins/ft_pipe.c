/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:25:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/21 21:56:05 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	exec_command(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	info->cmd_tree = node;
	if (check_builtins(info) == 0)
		exit(0);
    if (node->type == CMD)
	    exec(info, node);
	exit(1);
}

void	ft_pipe(t_info *info, t_tree *node, int infile)
{
	int		fd[2];
	pid_t	pid;

	if (!node)
		return ;
	if (node->type == PIPE)
	{
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("Pipe error\n", 2);
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Fork error\n", 2);
			exit(1);
		}
		if (pid == 0)
		{
			// Processo filho: executa lado esquerdo (node->left)
			close(fd[0]);
			if (infile != -1)
			{
				dup2(infile, STDIN_FILENO);
				close(infile);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
            
			ft_pipe(info, node->left, -1); // Recurse left
		}
		if (infile != -1)
			close(infile);
		close(fd[1]);
		ft_pipe(info, node->right, fd[0]); // Recurse right
		close(fd[0]);
	}
	else if (node->type == CMD)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Fork error\n", 2);
			exit(1);
		}
		if (pid == 0)
		{
			if (infile != -1)
			{
				dup2(infile, STDIN_FILENO);
				close(infile);
			}
			exec_command(info, node); // Apenas CMD chega aqui
		}
		if (infile != -1)
			close(infile);
	}
}

    

void	ft_pipe_wrapper(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;
	ft_pipe(info, info->cmd_tree, -1);
    while (wait(NULL) > 0);
}
