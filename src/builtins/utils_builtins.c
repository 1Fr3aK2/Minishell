/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/08 16:53:11 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_heredoc_fd(t_info *info)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		close(info->io->fd_in);
		info->io->fd_in = -1;
		info->io->stdin_is_heredoc = 0;
	}
}

int	apply_redirections_node(t_tree *node, int *saved_in, int *saved_out)
{
	if (node->io && node->io->fd_in != -1)
	{
		*saved_in = dup(STDIN_FILENO);
		if (*saved_in == -1 || dup2(node->io->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(node->io->fd_in);
		node->io->fd_in = -1;
	}
	if (node->io && node->io->fd_out != -1)
	{
		*saved_out = dup(STDOUT_FILENO);
		if (*saved_out == -1 || dup2(node->io->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(node->io->fd_out);
		node->io->fd_out = -1;
	}
	return (0);
}

int	is_builtin(char **builtins, char *cmd)
{
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], cmd, ft_strlen(builtins[i])) == 0
			&& ft_strlen(cmd) == ft_strlen(builtins[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_builtins(char **cmd, t_info *info, t_tree *node)
{
	int	saved_in;
	int	saved_out;

	saved_in = -1;
	saved_out = -1;
	process_redirections(node, info);
	if (info->exit_status == 258)
		return (0);
	if (apply_redirections_node(node, &saved_in, &saved_out) < 0)
		return (0);
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		ft_cd(info);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		ft_echo_wrapper(info, node);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		ft_env(info);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		ft_exit(info);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		ft_export_wrapper(info, node);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		ft_unset(info);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		ft_pwd(info);
	return (restore_redirections(saved_in, saved_out), 0);
}

void	exec_command(t_info *info, t_tree *node)
{
	exec(info, node);
	close_heredoc_fd(info);
	close_fds(0);
	ft_exit2(info);
}
