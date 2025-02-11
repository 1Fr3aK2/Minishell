/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:25:52 by raamorim          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/02/11 16:17:41 by dsteiger         ###   ########.fr       */
=======
/*   Updated: 2025/02/11 16:12:35 by raamorim         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	fill_builtins(t_info *info)
{
	info->builtins->builtins[0] = "echo";
	info->builtins->builtins[1] = "cd";
	info->builtins->builtins[2] = "pwd";
	info->builtins->builtins[3] = "export";
	info->builtins->builtins[4] = "unset";
	info->builtins->builtins[5] = "env";
	info->builtins->builtins[6] = "exit";
	info->builtins->builtins[7] = NULL;
	info->builtins->f[0] = ft_echo;
	info->builtins->f[1] = NULL;
	info->builtins->f[2] = ft_pwd;
	info->builtins->f[3] = NULL;
	info->builtins->f[4] = NULL;
	info->builtins->f[5] = NULL;
	info->builtins->f[6] = ft_exit;
	info->builtins->f[7] = NULL;
}

static void	init_builtins(t_info *info)
{
	int	i;

	if (!info)
		return ;
	i = 0;
	fill_builtins(info);
	// while (info->builtins->builtins[i])
	// {
	// 	printf("\n%s", info->builtins->builtins[i]);
	// 	i++;
	// }
	printf("\n");
}

static void	copy_env(t_info *info, char **env)
{
	int	i;
	int	j;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
		i++;
	info->my_env = ft_calloc(sizeof(char **), (i + 1));
	if (!info->my_env)
		return ;
	j = -1;
	while (++j < i)
	{
		info->my_env[j] = ft_strdup(env[j]);
		if (!info->my_env[j])
		{
			while (--j >= 0)
				free(info->my_env[j]);
			free(info->my_env);
			return ;
		}
	}
}

void	init(t_info *info, char **env)
{
	info->args = NULL;
	info->builtins = malloc(sizeof(t_builtins));
	if (!info->builtins)
		return ;
	init_builtins(info);
	copy_env(info, env);
}
