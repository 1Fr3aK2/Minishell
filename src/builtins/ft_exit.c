/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/06 17:48:39 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// sai do processo filo dentro de pipes cat Markefile | exit

void	ft_exit(t_info *info)
{
	unsigned int	status;
	int				exit_flags;

	status = 0;
	exit_flags = ft_atoi(info->flags);
	//caso (!info->flags) tens de tornar info->flags para 0, testa quando nao passas nada e fazes echo $?

	
	if (isatty(STDIN_FILENO)) // returns 1 if the fd is a terminal
		printf("exit\n");     // exit -> terminal. echo ola | exit -> not terminal
	if (exit_flags)
	{
		if (exit_flags > 255)
			status = exit_flags % 256;
		else
			status = exit_flags;
	}
	if (info->args)
	{
		free_arr(info->args);
		if (info->flags)
			free(info->flags);
		info->args = NULL;
	}
	free_builtins(info->builtins);
	free_arr(info->my_env);
	rl_clear_history();
	// clean(info);
	close_fds(0);
	exit(status);
}
