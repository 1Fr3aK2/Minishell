/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/11 14:37:54 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void child_process(t_info *info)
{	
	if (!info)
		return ;
	if (check_builtins(info) == 1)
		exec(info);
}
static char *get_env(char *variable_name, char **env)
{
	int i;
	int len;
	char *value;
	
	if (!variable_name || !env || !*env)
		return (NULL);
	i = 0;
	len = ft_strlen(variable_name);
	while(env[i])
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
static char *join_paths(char *path, char *cmd)
{
	char *dir;
	char *full_path;

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

static char *check_paths(char **paths, char *cmd)
{
	int				i;
	char *correct_path;
	
	if (!paths || !*paths || !cmd)
		return (NULL);
	i = 0;
	while(paths[i])
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


char *find_path(t_info *info)
{
	char **paths;
	char *path;
	
	if (!info)
		return (NULL);
	if (access(info->args[0], F_OK | X_OK) == 0)
    	return (info->args[0]);
	paths = custom_ft_split(get_env("PATH", info->my_env), ':');
	if (!paths)
		return (NULL);
	path = check_paths(paths, info->args[0]);
	return (path);
}

void exec(t_info *info)
{
	char *path;
	
	if (!info)
		return ;
	path = find_path(info);
	if (!path)
	{
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->args);
		exit(127);
	}
	if (execve(path, info->args, info->my_env) == -1)
	{
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->args);
		free(path);
		exit(126);
	}
}
