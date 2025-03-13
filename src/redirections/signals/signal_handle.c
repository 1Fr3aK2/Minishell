/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:48 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/12 18:51:08 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// ver comportamento sem input, mas na 3a instancia
void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "Quit (Core dumped)\n", 19);
	exit(131);
}

void	set_signals(void)
{
    signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
    write(1, "\n", 1);
}

// ver se est rl_end é necessaria
void	handle_ctrl_d(t_info *info)
{
	// If the input line is empty, exit the shell
	if (rl_end == 0) // rl_end is a variable of readline that contains the length of the current input line
	{
		printf("exit\n");
		rl_clear_history();
		free_arr(info->args);
		exit(0);
	}
}
