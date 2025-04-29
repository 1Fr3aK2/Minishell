/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:40:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/23 20:07:36 by rafael           ###   ########.fr       */
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
	char	**args;

	args = info->cmd_tree->args;
	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (info->redirections->reds[j])
		{
			if (ft_strncmp(args[i], info->redirections->reds[j],
					ft_strlen(args[i])) == 0)
			{
				info->io->file = ft_strdup(args[i + 1]);
				info->redirections->f[j](info->io);
				remove_redir_tokens(args, i);
				break ;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	remove_redir_tokens(char **args, int i)
{
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
	while (args[i + 2])
	{
		args[i] = args[i + 2];
		i++;
	}
	args[i] = NULL;
}
