/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:55:29 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/04 19:10:18 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void    ft_env(t_info *info)
{
    int i;

    i = 0;
    if (info->args && info->args[0] && info->args[1])
        return ;
    while (info->my_env && info->my_env[i])
    {
        write(1, info->my_env[i], ft_strlen(info->my_env[i]));
        write(1, "\n", 1);
        i++;
    }
}