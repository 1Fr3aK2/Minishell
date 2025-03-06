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
// so funciona se tiver no shellinho ou antes. Se fizer cd src, cd .. ja nao funciona
/* void	ft_cd_doispontos(t_info *info)
{
	static char	*cur_dir;
	char		*new_dir;
	int			len;

	len = 0;
	cur_dir = getcwd(NULL, PATH_MAX); // /home/dsteiger/shellinho
	while (cur_dir[len])
		len++;
	while (cur_dir[len] != '/') // len = /home/dsteiger/
		len--;
	new_dir = malloc(sizeof(char) * (len + 1));
	if (!new_dir)
		return ;
	if (!cur_dir[len - 1]) // Se so houver uma barra '/'
		ft_strncpy(new_dir, cur_dir, len + 1);
	else
		ft_strncpy(new_dir, cur_dir, len);
	new_dir[++len] = '\0';
	if (ft_strncmp(info->args[1], "..", 2) == 0)
		chdir(new_dir);
	free(new_dir);
} */

void ft_cd_doispontos(t_info *info)
{
	(void)info;
    char cur_dir[PATH_MAX];
    if (getcwd(cur_dir, sizeof(cur_dir)) != NULL)
    {
        // Find the last occurrence of '/'
        char *last_slash = strrchr(cur_dir, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0'; // Terminate the string at the last '/'
            if (chdir(cur_dir) != 0)
            {
                perror("chdir");
            }
        }
        else
        {
            // Already at the root directory
            fprintf(stderr, "Already at the root directory.\n");
        }
    }
    else
    {
        perror("getcwd");
    }
}

// funciona, vai pra HOME
void	ft_cd_simples(t_info *info)
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
// usar strncmp is not good because it need to work with cd (space after)
void	ft_cd(t_info *info)
{
	char	*oldpwd;

	if (info && info->args && info->args[1] && ft_strncmp(info->args[1], "..", 2) == 0)
		ft_cd_doispontos(info);
	else if (info && info->args && (!info->args[1] || ft_strncmp(info->args[1], "~", 1) == 0))
		ft_cd_simples(info);
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
