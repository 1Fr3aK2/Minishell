/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:16:58 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/04 19:15:14 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void    ft_unset(t_info *info)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (info->args[1] == NULL)
        return ;
    while (info->args[i])
    {
        while (info->my_env[j])
        {
            if (info->args[i] == info->my_env[j])
            {
            
            }
        }
        j++;
    }
    i++;
}