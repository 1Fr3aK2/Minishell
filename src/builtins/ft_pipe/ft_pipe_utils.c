/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:47:41 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:14:45 by rafael           ###   ########.fr       */
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

void	handle_heredoc(t_tree *node)
{
	if (node && node->io && node->io->heredoc_fd != -1)
	{
		if (dup2(node->io->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(1);
		}
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
}

void	exec_comand_op(t_info *info, t_tree *node)
{
	if (node->type == PIPE)
		ft_pipe(info, node);
	else
		exit(127);
}

void	execute_node(t_info *info, t_tree *node)
{
	if (node->type == CMD)
	{
		if (is_builtin(info->builtins->builtins, node->args[0]) == 0)
			exec_builtins(node->args, info, node);
		else
			exec_command(info, node);
	}
	else
		exec_comand_op(info, node);
}
