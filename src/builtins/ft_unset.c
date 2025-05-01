/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:16:58 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/09 19:21:23 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static int	is_match(char *env_var, char *arg)
{
	char	*str;
	size_t	len;
	int		match;

	str = reverse_strchr(env_var, '=');
	if (!str)
		str = env_var;
	len = ft_strlen(str);
	match = (ft_strncmp(arg, str, len) == 0
			&& (arg[len] == '\0' || arg[len] == '='));
	if (str != env_var)
		free(str);
	return (match);
}

static void	remove_env(char **env, int index)
{
	free(env[index]);
	while (env[index + 1])
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

static void	unset_from_env(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_match(env[i], arg))
		{
			remove_env(env, i);
			break ;
		}
		i++;
	}
}

void	ft_unset(t_info *info)
{
	int	i;

	if (!info->cmd_tree->args[1])
		return ;
	i = 1;
	while (info->cmd_tree->args[i])
	{
		unset_from_env(info->export_env, info->cmd_tree->args[i]);
		unset_from_env(info->my_env, info->cmd_tree->args[i]);
		i++;
	}
}
