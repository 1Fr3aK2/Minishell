/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:44:02 by rafael            #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_all(pid_t last_pid, t_info *info)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			update_status(info, WEXITSTATUS(status));
		else if (wpid == last_pid && WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				update_status(info, 131);
				write(1, "Quit (core dumped)\n", 19);
			}
			else if (WTERMSIG(status) == SIGINT)
				update_status(info, 130);
		}
		wpid = wait(&status);
	}
}

static void	close_exit(void)
{
	close_fds(0);
	exit(0);
}

void	exec_command(t_info *info, t_tree *node)
{
	info->cmd_tree = node;
	if (check_redirections(info) == 0)
		exit(0);
	if (node->type == CMD)
	{
		if (check_operators(info) == 0)
			exit(0);
		if (check_builtins(info) == 0)
			close_exit();
		else
		{
			exec(info, node);
			close_fds(0);
		}
	}
	else if (node->type == PIPE)
		ft_pipe(info, node);
	else if (node->type == AND)
		ft_and(info, node);
	else if (node->type == OR)
		ft_or(info, node);
	else
		exit(127);
	close_fds(0);
	exit(info->exit_status);
}
