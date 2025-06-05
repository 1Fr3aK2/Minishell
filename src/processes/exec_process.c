/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/06 00:03:51 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	exec(t_info *info, t_tree *node)
{
	char	*path;

	if (!info)
		return ;
	restore_io(info->io);
	path = find_path(info, node->args[0]);
	if (!path)
	{
		ft_putstr_fd(node->args[0], 2);
		free_arr(info->cmd_tree->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		close_fds(0);
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
