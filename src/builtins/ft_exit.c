/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/02 03:00:33 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// sai do processo filo dentro de pipes cat Markefile | exit

void	ft_exit(t_info *info)
{
	int				exit_flags;

	exit_flags = ft_atoi(info->flags);	
	if (isatty(STDIN_FILENO)) // returns 1 if the fd is a terminal
		printf("exit\n");     // exit -> terminal. echo ola | exit -> not terminal
	if (exit_flags)
	{
		if (exit_flags > 255)
			exit_status = exit_flags % 256;
		else
			exit_status = exit_flags;
	}
	free_tree(info->cmd_tree);
	free_builtins(info->builtins);
	free_arr(info->my_env);
	free_arr(info->export_env);
	rl_clear_history();
	close_fds(0);
	exit(exit_status);
}
// verificar exit status ctrl+d