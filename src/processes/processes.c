/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/19 13:26:27 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	child_process(t_info *info)
{
	pid_t	pid;

	if (!info)
		return ;
	if (check_builtins(info) == 1)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			exec(info);
		wait(NULL);
	}
}

void	exec(t_info *info)
{
	char	*path;

	if (!info)
		return ;
	path = find_path(info);
	if (!path)
	{
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		exit(127);
		//libertar tudo pois esta num child process que herda tudo do 
		//pai incluindo memoria e deve ser tudo libertado ao sair
	}
	if (execve(path, info->args, info->my_env) == -1)
	{
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		free(path);
		exit(126);
	}
}
