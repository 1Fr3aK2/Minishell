/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:25:15 by rafael            #+#    #+#             */
/*   Updated: 2025/05/10 02:52:47 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	exec_command_op(t_info *info, t_tree *node)
{
	pid_t	pid;
	int		status;

	if (check_builtins(info) == 0)
		return ;
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork error\n", 2);
		return ;
	}
	if (pid == 0)
		exec_command(info, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	ft_or(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	if (node->type == OR)
	{
		if (node->left && node->right)
		{
			ft_or(info, node->left);
			if (g_exit_status != 0)
				ft_or(info, node->right);
		}
		else
		{
			ft_putstr_fd("Shellinho: syntax error\n", 2);
			g_exit_status = 2;
			free_tree(node);
		}
	}
	else
		exec_command_op(info, node);
}

void	ft_or_wrapper(t_info *info)
{
	if (!info)
		return ;
	ft_or(info, info->cmd_tree);
}
