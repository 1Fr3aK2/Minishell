/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:44:02 by rafael            #+#    #+#             */
/*   Updated: 2025/05/13 18:09:54 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

void	wait_all(pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (wpid == last_pid && WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				g_exit_status = 131;
				write(1, "Quit (core dumped)\n", 19);
			}
			else if (WTERMSIG(status) == SIGINT)
			{
				g_exit_status = 130;
				write(1, "\n", 1);
			}
		}
		wpid = wait(&status);
	}
}

void	exec_command(t_info *info, t_tree *node)
{
	if (!info || !node)
		exit(1);
	info->cmd_tree = node;
	prepare_heredocs(info->cmd_tree, info);
	if (check_redirections(info) == 0)
		exit(0);
	if (node->type == CMD)
	{
		if (check_operators(info) == 0)
			exit(0);
		if (check_builtins(info) == 0)
			exit(0);
		exec(info, node);
	}
	else if (node->type == PIPE)
		ft_pipe(info, node);
	else if (node->type == AND)
		ft_and(info, node);
	else if (node->type == OR)
		ft_or(info, node);
	else
		exit(127);
	exit(g_exit_status);
}
