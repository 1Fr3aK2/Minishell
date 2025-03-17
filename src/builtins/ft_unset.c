/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:16:58 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/17 10:28:24 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void    ft_unset(t_info *info)
{
    int i;
    int j;
    int k;
    size_t len;

    if (info->cmd_tree->args[1] == NULL)
        return ;
    i = 1;
    while (info->cmd_tree->args[i])
    {
        j = 0;
        len = ft_strlen(info->cmd_tree->args[i]);
        while (info->my_env[j])
        {
            if (ft_strncmp(info->cmd_tree->args[i], info->my_env[j], len) == 0 && info->my_env[j][len] == '=')
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
