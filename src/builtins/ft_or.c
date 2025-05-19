/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:25:15 by rafael            #+#    #+#             */
/*   Updated: 2025/05/19 13:36:30 by raamorim         ###   ########.fr       */
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
		info->exit_status = WEXITSTATUS(status);
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
			if (info->exit_status != 0)
				ft_or(info, node->right);
		}
		else
		{
			ft_putstr_fd("Shellinho: syntax error\n", 2);
			update_status(info, 2);
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
	prepare_heredocs(info->cmd_tree, info);
	ft_or(info, info->cmd_tree);
}
