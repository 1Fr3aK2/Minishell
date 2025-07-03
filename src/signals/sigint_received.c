/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_received.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:48 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/03 03:43:15 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_received(t_info *info)
{
	if (g_sigint_received)
	{
		info->exit_status = 130;
		g_sigint_received = 0;
	}
}

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_parent_signals(int status, t_info *info)
{
	if (WIFEXITED(status))
		update_status(info, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			update_status(info, 131);
			write(1, "Quit (core dumped)\n", 19);
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			update_status(info, 130);
			write(1, "\n", 1);
		}
	}
}
