/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/23 15:18:58 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
path-> is the path the user wants to change to
chdir -> this changed the dir to what I wanted
getcwd -> this retrieved the path I wanted
*/

/* COUNT LEVELS
strstr -> Count how many "../" there is /
find the 1st occurence of "..". Pointer points to the beginning of ".."

ptr += 2 -> Move past the ".."
ptr++ -> Move past the "/"
len -> updates the len to exclude the "../" that have been iterated
*/

/*
if (last_slash == cur_dir) // the last slash if the 1st character (/)
*/

#include "../../includes/shellinho.h"

void	cd_with_arg(const char *path)
{
	char	current_dir[PATH_MAX];

    if (!path)
	{
		error_exit("Error: path is NULL");
		return;
	}
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

int count_levels(const char *arg)
{
    int levels;
    const char *ptr;
    size_t len;
    
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
            error_exit("Error: Invalid directory path");
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

void	ft_cd_home(t_info *info)
{
    char *home_path;

    if (!info || !info->cmd_tree->args)
    {
        printf("Error: Invalid info or args\n");
        return;
    }
    home_path = getenv("HOME");
    if (!home_path)
    {
        printf("HOME not set\n");
        return;
    }
    if (chdir(home_path) == -1)
    {
        printf("cd: Directory change failed\n");
        return;
    }
}

void	ft_cd(t_info *info)
{
    int     levels;

    if (!info || !info->cmd_tree->args)
    {
        ft_putstr_fd("Error: Invalid info or args\n", 2);
        return;
    }
	if ((!info->cmd_tree->args[1] || ft_strncmp(info->cmd_tree->args[1], "~", 1) == 0))
        ft_cd_home(info);
    else if (info->cmd_tree->args[1] && ft_strncmp(info->cmd_tree->args[1], "..", 2) == 0)
    {
        levels = count_levels(info->cmd_tree->args[1]);
        ft_cd_doispontos(info, levels);
	}
	else if (info->cmd_tree->args[1])
		cd_with_arg(info->cmd_tree->args[1]);
}
