/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/06 19:27:13 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// all good
void	cd_with_arg(const char *path)
{
	char	current_dir[PATH_MAX];

	if (chdir(path) == 0)
	{
		if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			;
		else
			error_exit("Error: getcwd");
	}
	else
		error_exit("Error: chdir");
}

// all good
int count_levels(const char *arg)
{
    int levels;
    const char *ptr;
    size_t len;
    
    levels = 0;
    ptr = arg;
    len = ft_strlen(ptr);
    // Count how many "../" there is
    while ((ptr = ft_strnstr(ptr, "..", len))) // find the 1st occurence of "..". Pointer points to the beginning of ".."
    {
        levels++;
        ptr += 2; // Move past the ".."
        if (*ptr == '/')
            ptr++; // Move past the "/"
        len = ft_strlen(ptr); // updates the len to exclude the "../" that have been iterated
    }
    return (levels);
}

// all good
void ft_cd_doispontos(t_info *info, int levels)
{
    (void)info;
    char cur_dir[PATH_MAX];
    char *last_slash;
    int i;

    i = 0;
    if (getcwd(cur_dir, sizeof(cur_dir)) == NULL)
        error_exit("Error: getcwd");
    while (i < levels)
    {
        last_slash = ft_strrchr(cur_dir, '/');
        if (last_slash == NULL)
            error_exit("Error: Already at the root directory");
        if (last_slash == cur_dir)
        {
            *last_slash = '\0';
            break;
        }
        *last_slash = '\0';
        i++;
    }

    if (chdir(cur_dir) != 0)
            error_exit("Error: chdir");
}

// all good, vai pra HOME
void	ft_cd_home(t_info *info)
{
	char	*home_path;

	if (info || info->args || !info->args[1])
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			printf("HOME not set\n");
			return ;
		}
		if (chdir(home_path) == -1)
		{
			printf("cd: Directory change failed");
			return ;
		}
	}
	return ;
}

void	ft_cd(t_info *info)
{
	char	*oldpwd;
    int levels;
    levels = count_levels(info->args[1]);

	if (info && info->args && info->args[1] && ft_strncmp(info->args[1], "..", 2) == 0)
		ft_cd_doispontos(info, levels);
	else if (info && info->args && (!info->args[1] || ft_strncmp(info->args[1], "~", 1) == 0))
		ft_cd_home(info);
	else if (info && info->args && info->args[1] && ft_strncmp(info->args[1], "-", 1) == 0) // this does not work
	{
		oldpwd = getenv("OLDPWD");
		if (oldpwd)
			cd_with_arg(oldpwd);
		else
			error_exit("Error: OLDPWD not set");
	}
	else if (info && info->args && info->args[1])
		cd_with_arg(info->args[1]);
}
