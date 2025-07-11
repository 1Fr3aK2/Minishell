/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:15 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/03 00:15:33 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char *variable_name, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!variable_name || !env || !*env)
		return (NULL);
	i = 0;
	len = ft_strlen(variable_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], variable_name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strchr(env[i], '=');
			if (!value)
				return (NULL);
			else
				return (value + 1);
		}
		i++;
	}
	return (NULL);
}

static char	*join_paths(char *path, char *cmd)
{
	char	*dir;
	char	*full_path;

	if (!path || !cmd)
		return (NULL);
	dir = ft_strjoin(path, "/");
	if (!dir)
		return (NULL);
	full_path = ft_strjoin(dir, cmd);
	free(dir);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static char	*check_paths(char **paths, char *cmd)
{
	int		i;
	char	*correct_path;

	if (!paths || !*paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		correct_path = join_paths(paths[i], cmd);
		if (!correct_path)
			return (NULL);
		if (access(correct_path, F_OK | X_OK) == 0)
		{
			free_arr(paths);
			return (correct_path);
		}
		free(correct_path);
		i++;
	}
	free_arr(paths);
	return (NULL);
}

char	*find_path(t_info *info, char *cmd)
{
	char	**paths;
	char	*path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		return (ft_strdup(cmd));
	}
	paths = ft_split(get_env("PATH", info->my_env), ':');
	if (!paths)
		return (NULL);
	path = check_paths(paths, cmd);
	if (!path)
		return (NULL);
	return (path);
}

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	if (errno == ENOTDIR)
		return (0);
	return (0);
}
