/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:40:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/16 19:02:38 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_redirections(t_info *info, int *saved_in, int *saved_out)
{
	if (info->io->fd_in != -1)
	{
		*saved_in = dup(STDIN_FILENO);
		if (*saved_in == -1 || dup2(info->io->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(info->io->fd_in);
		info->io->fd_in = -1;
	}
	if (info->io->fd_out != -1)
	{
		*saved_out = dup(STDOUT_FILENO);
		if (*saved_out == -1 || dup2(info->io->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(info->io->fd_out);
		info->io->fd_out = -1;
	}
	return (0);
}

void	restore_redirections(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	check_builtins(t_info *info)
{
	char	*cmd;
	int		i;
	int		saved_in;
	int		saved_out;

	saved_in = -1;
	saved_out = -1;
	cmd = info->cmd_tree->args[0];
	i = 0;
	while (info->builtins->builtins[i])
	{
		if (ft_strncmp(cmd, info->builtins->builtins[i],
				ft_strlen(info->builtins->builtins[i])) == 0
			&& ft_strlen(cmd) == ft_strlen(info->builtins->builtins[i]))
		{
			if (apply_redirections(info, &saved_in, &saved_out) == -1)
				return (0);
			if (info->builtins->f[i])
				info->builtins->f[i](info);
			restore_redirections(saved_in, saved_out);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_operators(t_info *info)
{
	char	*cmd;
	int		i;

	if (!info || !info->cmd_tree)
		return (1);
	i = 0;
	cmd = info->cmd_tree->args[0];
	while (info->types->types[i])
	{
		if (ft_strncmp(cmd, info->types->types[i],
				ft_strlen(info->types->types[i])) == 0)
		{
			if (ft_strlen(cmd) == ft_strlen(info->types->types[i]))
			{
				if (info->types->f[i])
					info->types->f[i](info);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_redirections(t_info *info)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (info->cmd_tree->args && info->cmd_tree->args[i])
	{
		j = 0;
		while (info->redirections->reds[j])
		{
			if (ft_strncmp(info->cmd_tree->args[i], info->redirections->reds[j],
					ft_strlen(info->cmd_tree->args[i])) == 0)
			{
				if (!info->cmd_tree->args[i + 1])
					return (1);
				update_io_file(info->io, info->cmd_tree->args[i + 1]);
				ret = info->redirections->f[j](info->io, info);
				if (ret < 0)
					return (-1);
				remove_redir_tokens(info->cmd_tree->args, i);
				j = -1;
			}
			j++;
		}
		i++;
	}
	return (1);
}
