/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/23 20:16:32 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* static void	handle_child_process(t_info *info, t_tree *node)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		dup2(info->io->fd_in, STDIN_FILENO);
		close(info->io->fd_in);
	}
	exec_command(info, node);
} */
static void	close_heredoc_fd(t_info *info)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		close(info->io->fd_in);
		info->io->fd_in = -1;
		info->io->stdin_is_heredoc = 0;
	}
}
/*
static void	handle_status(t_info *info, int status)
{
	int	sig;

	if (WIFEXITED(status))
		update_status(info, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			update_status(info, 130);
		else if (sig == SIGQUIT)
		{
			update_status(info, 131);
			write(1, "Quit (core dumped)\n", 19);
		}
	}
} */

int is_builtin(char **builtins, char *cmd)
{
	int i;
	i = 0;
	while(builtins[i])
	{
		if (ft_strncmp(builtins[i], cmd, ft_strlen(builtins[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}

int exec_builtins(char **cmd, t_info *info, t_tree *node)
{
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(info), 0);
	if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo_wrapper(info, node), 0);
	if (ft_strncmp(cmd[0], "env", ft_strlen("env")) == 0)
		return (ft_env(info), 0);
	if (ft_strncmp(cmd[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(info), 0);
	if (ft_strncmp(cmd[0], "export", ft_strlen("export")) == 0)
		return (ft_export(info), 0);
	if (ft_strncmp(cmd[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(info), 0);
	if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(info), 0);
	return (1);
}

void	exec_command_op(t_info *info, t_tree *node)
{
	/* if (check_builtins(info) == 0)
	{
		close_heredoc_fd(info);
		close_fds(0);
		exit(info->exit_status);
	} */
	exec(info, node);
	close_heredoc_fd(info);
	close_fds(0);
	exit(info->exit_status);
}
