/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:58 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/25 00:39:09 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static void	handle_child_process(t_info *info, t_tree *node)
{
	if (info->io->stdin_is_heredoc && info->io->fd_in != -1)
	{
		dup2(info->io->fd_in, STDIN_FILENO);
		close(info->io->fd_in);
	}
	exec_comand_op(info, node);
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
	int	i;
	int	i;
	int	i;

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

int	check_redirections_node(t_tree *node, t_info *info)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (node->args && node->args[i])
	{
		j = 0;
		while (info->redirections->reds[j])
		{
			if (ft_strncmp(node->args[i], info->redirections->reds[j],
					ft_strlen(node->args[i])) == 0)
			{
				if (!node->args[i + 1])
					return (1);
				update_io_file(node->io, node->args[i + 1]); 
				ret = info->redirections->f[j](node->io, info);
				if (ret < 0)
					return (-1);
				remove_redir_tokens(node->args, i);
				j = -1;
			}
			j++;
		}
		i++;
	}
	return (1);
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
	if (check_redirections_node(node, info) < 0)
		return (0);
	if (apply_redirections_node(node, &saved_in, &saved_out) < 0)
		return (0);
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
		ft_cd(info);
	else if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
		ft_echo_wrapper(info, node);
	else if (ft_strncmp(cmd[0], "env", ft_strlen("env")) == 0)
		ft_env(info);
	else if (ft_strncmp(cmd[0], "exit", ft_strlen("exit")) == 0)
		ft_exit(info);
	else if (ft_strncmp(cmd[0], "export", ft_strlen("export")) == 0)
		ft_export_wrapper(info, node);
	else if (ft_strncmp(cmd[0], "unset", ft_strlen("unset")) == 0)
		ft_unset(info);
	else if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(info);
	else
		return (restore_redirections(saved_in, saved_out), 1);
	restore_redirections(saved_in, saved_out);
	return (0);
}


void	exec_command(t_info *info, t_tree *node)
{
	exec(info, node);
	close_heredoc_fd(info);
	close_fds(0);
	exit(info->exit_status);
}
