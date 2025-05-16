/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/16 20:22:48 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	handle_parent_signals(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_exit_status = 131;
			write(1, "Quit (Core dumped)\n", 19);
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			g_exit_status = 130;
			write(1, "\n", 1);
		}
	}
}

static void	exec_child_process(t_info *info)
{
	handle_child_signals();
	exec(info, info->cmd_tree);
	exit(1);
}

void	child_process(t_info *info)
{
	pid_t	pid;
	int		status;

	if (!info)
		return ;
	storing_backup(info->io);
	g_exit_status = 0;
	prepare_heredocs(info->cmd_tree, info);
	if (g_exit_status == 130)
		return ;
	check_redirections(info);
	if (g_exit_status == 130)
		return ;
	free_io_file(info->io);
	info->io->file = NULL;
	if (!check_operators(info) || !check_builtins(info))
		return (restore_io(info->io));
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_child_process(info);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	restore_io(info->io);
	set_signals();
	signal(SIGINT, handle_sigint);
	handle_parent_signals(status);
}

void	exec(t_info *info, t_tree *node)
{
	char	*path;

	if (!info)
		return ;
	path = find_path(info, node->args[0]);
	if (!path)
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->cmd_tree->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		exit(127);
	}
	if (execve(path, node->args, info->my_env) == -1)
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->cmd_tree->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		free(path);
		exit(126);
	}
}
