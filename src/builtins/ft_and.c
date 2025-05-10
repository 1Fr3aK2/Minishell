/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/10 02:52:26 by rafael           ###   ########.fr       */
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
			if (g_exit_status == 0)
				ft_and(info, node->right);
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

void	ft_and_wrapper(t_info *info)
{
	if (!info)
		return ;
	ft_and(info, info->cmd_tree);
}
