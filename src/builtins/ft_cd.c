/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/20 18:10:31 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	ft_cd_doispontos(t_info *info)
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

}

// this is just for cd alone
void	ft_cd_simples(t_info *info)
{
	char	*home_path;

	// check if there's an info struct,
	// if arg list in NULL and if there's no arg after cd
	if (!info || !info->args || !info->args[1])
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
	// Check if the user wants to go to the parent directory (cd ..)
	if (info && info->args && info->args[1] && strncmp(info->args[1], "..", 2) == 0)
		ft_cd_doispontos(info);
	// If no argument or just 'cd', go to the home directory
	else
		ft_cd_simples(info);
}