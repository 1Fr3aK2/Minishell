/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_with_arg(const char *path, t_info *info)
{
	char	current_dir[PATH_MAX];

	if (!path)
	{
		info->exit_status = 1;
		return ;
	}
	if (chdir(path) == 0)
	{
		if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			;
		else
		{
			ft_putstr_fd("Error: getcwd\n", 2);
			info->exit_status = 1;
		}
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		info->exit_status = 1;
	}
}

int	count_levels(const char *arg)
{
	int			levels;
	const char	*ptr;
	size_t		len;

	levels = 0;
	ptr = arg;
	len = ft_strlen(ptr);
	while (1)
	{
		ptr = ft_strnstr(ptr, "..", len);
		if (!ptr)
			break ;
		levels++;
		ptr += 2;
		if (*ptr == '/')
			ptr++;
		len = ft_strlen(ptr);
	}
	return (levels);
}

void	ft_cd_doispontos(t_info *info, int levels)
{
	char	cur_dir[PATH_MAX];
	char	*last_slash;
	int		i;

	(void)info;
	i = 0;
	if (!getcwd(cur_dir, sizeof(cur_dir)))
		ft_putstr_fd("Error: getcwd\n", 2);
	while (i < levels)
	{
		last_slash = ft_strrchr(cur_dir, '/');
		if (!last_slash)
			ft_putstr_fd("Error: Invalid directory path\n", 2);
		if (last_slash == cur_dir)
		{
			cur_dir[1] = '\0';
			break ;
		}
		*last_slash = '\0';
		i++;
	}
	if (chdir(cur_dir) != 0)
		ft_putstr_fd("Error: chdir\n", 2);
}

void	ft_cd_home(t_info *info)
{
	char	*home_path;

	if (!info || !info->cmd_tree->args)
	{
		ft_putstr_fd("Error: Invalid info or args\n", 2);
		return ;
	}
	home_path = getenv("HOME");
	if (!home_path)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return ;
	}
	if (chdir(home_path) == -1)
	{
		ft_putstr_fd("cd: Directory change failed\n", 2);
		return ;
	}
}

void	ft_cd(t_info *info)
{
	int	levels;

	if (!info || !info->cmd_tree->args)
	{
		info->exit_status = 1;
		return ;
	}
	if (info->cmd_tree->args[0] && info->cmd_tree->args[1]
		&& info->cmd_tree->args[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		info->exit_status = 1;
		return ;
	}
	if ((!info->cmd_tree->args[1] || ft_strncmp(info->cmd_tree->args[1], "~",
				1) == 0))
		ft_cd_home(info);
	else if (info->cmd_tree->args[1] && ft_strncmp(info->cmd_tree->args[1],
			"..", 2) == 0)
	{
		levels = count_levels(info->cmd_tree->args[1]);
		ft_cd_doispontos(info, levels);
	}
	else if (info->cmd_tree->args[1])
		cd_with_arg(info->cmd_tree->args[1], info);
}
