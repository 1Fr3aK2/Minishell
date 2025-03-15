/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/12 18:51:49 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	child_process(t_info *info)
{
	pid_t	pid;
    struct sigaction sa;
    int	status;

	if (!info)
		return ;
	if (check_builtins(info) == 1)
	{
        sa.sa_handler = handle_sigquit;
        sa.sa_flags = SA_RESTART; // Ensure the signal handler is restarted automatically
        sigemptyset(&sa.sa_mask);  // No additional signals to block
        sigaction(SIGQUIT, &sa, NULL); 
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
            exec(info);
        else
        {
            signal(SIGINT, SIG_IGN); // Ignore SIGINT while waiting to prevent duplicate prompts
            waitpid(pid, &status, 0);
            set_signals();  // Restore SIGINT handling after child exits
        }
	}
}

void	exec(t_info *info)
{
	char	*path;

	if (!info)
		return ;
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = find_path(info);
	if (!path)
	{
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		exit(127);
		// libertar tudo pois esta num child process que herda tudo do
		// pai incluindo memoria e deve ser tudo libertado ao sair
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
