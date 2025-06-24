/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:07:15 by rafael            #+#    #+#             */
/*   Updated: 2025/06/24 20:07:27 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_export_wrapper(t_info *info, t_tree *node)
{
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	check_redirections(info);
	if (!node->args[i])
		return (print_sorted_env(info->export_env));
	while (node->args[i])
	{
		if (!check_valid_input(node->args[i], &exit_status))
		{
			i++;
			continue ;
		}
		if (check_equal_plus(node->args[i]))
			handle_plus_assignment(info, node->args[i]);
		else if (check_equal_sign(node->args[i]))
			handle_regular_assignment(info, node->args[i]);
		else if (!check_env(&info->export_env, node->args[i]))
			add_to_env(&info->export_env, node->args[i]);
		i++;
	}
	update_status(info, exit_status);
}
