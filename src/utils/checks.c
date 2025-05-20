/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:40:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/20 14:55:45 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

int	check_builtins(t_info *info)
{
	char	*cmd;
	int		i;

	cmd = info->cmd_tree->args[0];
	i = 0;
	while (info->builtins->builtins[i])
	{
		if (ft_strncmp(cmd, info->builtins->builtins[i],
				ft_strlen(info->builtins->builtins[i])) == 0)
		{
			if (ft_strlen(cmd) == ft_strlen(info->builtins->builtins[i]))
			{
				if (info->builtins->f[i])
					info->builtins->f[i](info);
				return (0);
			}
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
	int		i;
	int		j;

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
				info->redirections->f[j](info->io);
				remove_redir_tokens(info->cmd_tree->args, i);
				j = -1;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	update_io_file(t_io *io, char *filename)
{
	if (io->file)
	{
		free(io->file);
		io->file = NULL;
	}
	io->file = ft_strdup(filename);
	if (!io->file)
		return ;
}

void	remove_redir_tokens(char **args, int i)
{
	int	j;

	if (args[i])
	{
		free(args[i]);
		args[i] = NULL;
	}
	if (args[i + 1])
	{
		free(args[i + 1]);
		args[i + 1] = NULL;
	}
	j = i + 2;
	while (args[j])
	{
		args[i++] = args[j++];
	}
	args[i] = NULL;
}
