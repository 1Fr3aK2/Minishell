/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:16:58 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/01 20:02:58 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	ft_unset(t_info *info)
{
	int		i;
	int		j;
	size_t	len;

	if (!info->cmd_tree->args[1])
		return ;
	i = 1;
	while (info->cmd_tree->args[i])
	{
		j = 0;
		while (info->export_env[j])
		{
            len = ft_strlen(info->cmd_tree->args[i]);
			if (ft_strncmp(info->cmd_tree->args[i], info->export_env[j],
					len) == 0) //  && (info->export_env[j][len] == '='|| info->export_env[j][len] == '\0')
			{
				free(info->export_env[j]);
				//free(info->my_env[j]);
				while (info->export_env[j + 1])
				{
					info->export_env[j] = info->export_env[j + 1];
					//info->my_env[j] = info->my_env[j + 1];
					j++;
				}
				info->export_env[j] = NULL;
				//info->my_env[j] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
}

/*
void	ft_unset(t_info *info)
{
	int		i;
	int		j;
	int		nbr_envs;
	size_t	len;

	if (!info->cmd_tree->args[1])
		return ;
	i = 1;
	nbr_envs = 0;
	while (info->cmd_tree->args[i + nbr_envs])
		nbr_envs++;
	while (info->cmd_tree->args[i])
	{
		j = 0;
		while (info->export_env[j + nbr_envs])
		{
			len = ft_strlen(info->cmd_tree->args[i]);
			if (ft_strncmp(info->cmd_tree->args[i], info->export_env[j
					+ nbr_envs],
					len) == 0 && (info->export_env[j][len] == '='
					|| info->export_env[j][len] == '\0'))
			{
				while (info->export_env[j + nbr_envs])
				{
					printf("%s\n", info->export_env[j + nbr_envs]);
					free(info->export_env[j + nbr_envs]);
					free(info->my_env[j + nbr_envs]);
					info->export_env[j] = info->export_env[j + nbr_envs];
					info->my_env[j] = info->my_env[j + nbr_envs];
					j++;
				}
				info->export_env[j + nbr_envs] = NULL;
				info->my_env[j + nbr_envs] = NULL;
				nbr_envs--;
			}
			j++;
		}
		i++;
	}
}
 */