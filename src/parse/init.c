/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:54:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/29 16:35:14 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	copy_env(char ***my_env, char **env)
{
	int	i;
	int	j;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
		i++;
	*my_env = ft_calloc((i + 1), sizeof(char *));
	if (!*my_env)
		return ;
	j = -1;
	while (++j < i)
	{
		(*my_env)[j] = ft_strdup(env[j]);
		if (!(*my_env)[j])
		{
			while (--j >= 0)
				free((*my_env)[j]);
			free(*my_env);
			return ;
		}
	}
}

void	init_io(t_io *io)
{
	if (!io)
		return ;
	io->fd_in = -1;
	io->fd_out = -1;
	io->stdin_backup = -1;
	io->stdin_backup = -1;
	io->file = NULL;
	io->redirections = NULL;
}

void	init(t_info *info)
{
	info->cmd_tree = NULL;
	info->flags = NULL;
	info->export_env = NULL;
	info->builtins = malloc(sizeof(t_builtins));
	if (!info->builtins)
		return ;
	info->types = malloc(sizeof(t_types));
	if (!info->types)
		return (free(info->builtins));
	info->redirections = malloc(sizeof(t_reds));
	if (!info->redirections)
	{
		free(info->builtins);
		free(info->types);
		return ;
	}
	info->io = malloc(sizeof(t_io));
	if (!info->io)
	{
		free(info->builtins);
		free(info->types);
		free(info->redirections);
		return ;
	}
	init_io(info->io);
	fill_all(info);
}
