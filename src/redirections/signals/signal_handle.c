/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:48 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 16:35:09 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

//signal(SIGQUIT, SIG_IGN); // SIGQUIT == CTRL \ , SIG_IGN tells the shell to ignore the signal

void    handle_sigint(int sig)
{

}

void    handle_sigquit(int sig)
{

}

void    set_signals(void)
{
    struct sigaction sa_sint;
    struct sigaction sa_squit;

    sa_sint.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &sa_sint, NULL) == -1)
        error_exit("SIGINT failed");

    sa_squit.sa_handler = handle_sigquit;
    if (sigaction(SIGQUIT, &sa_squit, NULL) == -1)
        error_exit("SIGQUIT failed");


}