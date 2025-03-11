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
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART; // quando estou na 3a instancia, escreve so shellinho$> 1x em vez de repetir varias vezes
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
		error_exit("SIGINT failed");
        exit(EXIT_FAILURE);
    }
	sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
    {
		error_exit("SIGQUIT failed");
        exit(EXIT_FAILURE);
    }
}
