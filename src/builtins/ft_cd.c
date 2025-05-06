/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/06 19:35:04 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	cd_with_arg(const char *path)
{
	char	current_dir[PATH_MAX];

	if (!path)
	{
		ft_putstr_fd("Error: path is NULL", 2);
		return ;
	}
	if (chdir(path) == 0)
	{
		if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			;
		else
			ft_putstr_fd("Error: getcwd", 2);
	}
	else
		ft_putstr_fd("Error: chdir", 2);
}

int	count_levels(const char *arg)
{
	int			levels;
	const char	*ptr;
	size_t		len;

	levels = 0;
	ptr = arg;
	len = ft_strlen(ptr);
	while ((ptr = ft_strnstr(ptr, "..", len)))
	{
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
	if (getcwd(cur_dir, sizeof(cur_dir)) == NULL)
		ft_putstr_fd("Error: getcwd", 2);
	while (i < levels)
	{
		last_slash = ft_strrchr(cur_dir, '/');
		if (last_slash == NULL)
			ft_putstr_fd("Error: Invalid directory path", 2);
		if (last_slash == cur_dir)
		{
			*last_slash = '\0';
			break ;
		}
		*last_slash = '\0';
		i++;
	}
	if (chdir(cur_dir) != 0)
		ft_putstr_fd("Error: chdir", 2);
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
		ft_putstr_fd("Error: Invalid info or args\n", 2);
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
		cd_with_arg(info->cmd_tree->args[1]);
}
