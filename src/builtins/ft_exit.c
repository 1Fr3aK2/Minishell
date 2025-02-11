/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/06 15:15:15 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"


// sai do processo filo dentro de pipes cat Markefile | exit

void ft_exit(t_info *info)
{
	unsigned int status;
	(void)info;

	status = 255;
	// if (exit_status < 0 || exit_status > 255)
	// 	status = 255;
	// else
	// 	status = exit_status;

	// if(input)
	// 	free(input);
	// if (info->args)
	// {
	// 	free_arr(info->args);
	// 	if (info->flags)
	// 		free(info->flags);
	// 	info->args = NULL;
	// }
	clean(info);
	rl_clear_history();
	close_fds(0);
	exit(status);
}