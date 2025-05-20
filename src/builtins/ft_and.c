/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/20 16:24:00 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	ft_and(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	if (node->type == AND)
	{
		if (node->left && node->right)
		{
			ft_and(info, node->left);
			if (info->exit_status == 0)
				ft_and(info, node->right);
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

void	ft_and_wrapper(t_info *info)
{
	if (!info)
		return ;
	prepare_heredocs(info->cmd_tree, info);
	ft_and(info, info->cmd_tree);
}
