/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/16 19:04:54 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_io_from_tree(t_info *info)
{
	if (info->cmd_tree && info->cmd_tree->io)
	{
		if (info->io->heredoc_fd != -1)
			close(info->io->heredoc_fd);
		info->io->heredoc_fd = info->cmd_tree->io->heredoc_fd;
		info->cmd_tree->io->heredoc_fd = -1;
		info->io->stdin_is_heredoc = info->cmd_tree->io->stdin_is_heredoc;
	}
}

static int	pre_fork_setup(t_info *info)
{
	prepare_heredocs(info->cmd_tree, info);
	if (info->exit_status == 130)
		return (0);
	storing_backup(info->io);
	setup_io_from_tree(info);
	check_redirections(info);
	if (info->exit_status != 0)
	{
		restore_io(info->io);
		return (0);
	}
	set_signals_noninteractive();
	free_io_file(info->io);
	info->io->file = NULL;
	close_io_fds(info->io);
	return (1);
}

static void	run_fork_and_exec(t_info *info)
{
	pid_t	pid;
	int		status;

	if (!check_builtins(info))
	{
		restore_io(info->io);
		return;
	}
	pid = fork();
	if (pid == -1)
		return;
	if (pid == 0)
		exec_child_process(info);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		set_signals_interactive();
		restore_io(info->io);
		handle_parent_signals(status, info);
	}
}



void	child_process(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;

	info->exit_status = 0;

	if (!pre_fork_setup(info))
		return ;

	t_tree *node = info->cmd_tree;
	if (node->type == CMD)
		run_fork_and_exec(info);
	else if (node->type == PIPE)
		ft_pipe_wrapper(info);
	else if (node->type == AND)
		ft_and(info, node);
	else if (node->type == OR)
		ft_or(info, node);
	else
		info->exit_status = 127;
}


