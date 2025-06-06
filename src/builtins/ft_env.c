/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:55:29 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_info *info)
{
	int	i;

	i = 0;
	if (info->cmd_tree->args && info->cmd_tree->args[0]
		&& info->cmd_tree->args[1])
		return ;
	remove_all_quotes(info->my_env);
	while (info->my_env && info->my_env[i])
	{
		write(1, info->my_env[i], ft_strlen(info->my_env[i]));
		write(1, "\n", 1);
		i++;
	}
}
