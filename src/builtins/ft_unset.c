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
    int k;
    size_t len;

    if (info->args[1] == NULL)
        return ;
    i = 1;
    while (info->args[i])
    {
        j = 0;
        len = ft_strlen(info->args[i]);
        while (info->my_env[j])
        {
            if (ft_strncmp(info->args[i], info->my_env[j], len) == 0 && info->my_env[j][len] == '=')
            {
                free(info->my_env);
                k = j;
                while (info->my_env[k])
                {
                    info->my_env[k] = info->my_env[k + 1];
                    k++;
                }
                info->my_env[k] = NULL;
            }
            else
                j++;
        }
    }
    i++;
}
