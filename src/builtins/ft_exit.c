/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/19 12:05:37 by raamorim         ###   ########.fr       */
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
	free_arr(info->my_env);
	rl_clear_history();
	// clean(info);
	close_fds(0);
	exit(status);
}
