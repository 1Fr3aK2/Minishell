/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:25:15 by rafael            #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_or(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	if (node->type == OR)
	{
		if (node->left && node->right)
		{
			ft_or(info, node->left);
			if (info->exit_status != 0 && info->exit_status != 130)
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
	ft_or(info, info->cmd_tree);
}
