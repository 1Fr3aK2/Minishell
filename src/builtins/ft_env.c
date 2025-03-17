/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:55:29 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/17 10:28:24 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void    ft_env(t_info *info)
{
    int i;

    i = 0;
    if (info->cmd_tree->args && info->cmd_tree->args[0] && info->cmd_tree->args[1])
        return ;
    while (info->my_env && info->my_env[i])
    {
        write(1, info->my_env[i], ft_strlen(info->my_env[i]));
        write(1, "\n", 1);
        i++;
    }
}