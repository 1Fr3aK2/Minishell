/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:40:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/03 04:03:24 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	handle_redirection(t_info *info, int i, int j)
{
	int	ret;

	if (!info->cmd_tree->args[i + 1])
		return (1);
	update_io_file(info->io, info->cmd_tree->args[i + 1]);
	ret = info->redirections->f[j](info->io, info);
	if (ret < 0)
		return (-1);
	remove_redir_tokens(info->cmd_tree->args, i);
	return (0);
}

int	check_redirections(t_info *info)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	while (info->cmd_tree->args && info->cmd_tree->args[i])
	{
		j = 0;
		while (info->redirections->reds[j])
		{
			if (ft_strncmp(info->cmd_tree->args[i], info->redirections->reds[j],
					ft_strlen(info->cmd_tree->args[i])) == 0)
			{
				res = handle_redirection(info, i, j);
				if (res == 1)
					return (1);
				if (res == -1)
					return (-1);
				j = -1;
			}
			j++;
		}
		i++;
	}
	return (1);
}
