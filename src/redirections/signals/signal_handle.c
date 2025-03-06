/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:48 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/06 17:40:42 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (!command_running)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0); // delete the input
		rl_redisplay(); // redisplay prompt
	}
	else
		printf("\n");
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (command_running)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		exit(1);
	}
	else
		return ;
}

void	set_signals(void)
{
	struct sigaction sa_sint;
	struct sigaction sa_squit;

	sa_sint.sa_handler = handle_sigint;
	sa_sint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sint, NULL) == -1)
		error_exit("SIGINT failed");

	sa_squit.sa_handler = handle_sigquit;
	sa_squit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_squit, NULL) == -1)
		error_exit("SIGQUIT failed");
}