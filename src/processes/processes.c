/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:53:00 by raamorim          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/03/26 19:42:01 by raamorim         ###   ########.fr       */
=======
/*   Updated: 2025/03/26 19:51:09 by dsteiger         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	child_process(t_info *info)
{
	pid_t	pid;
	int		status;

	if (!info)
		return ;
	if (check_operators(info) == 0)
		return ;
	if (check_builtins(info) == 1)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL); // processo filho tem comportamento padrao,
			signal(SIGQUIT, SIG_DFL);// independentemente das definicoes do processo pai
			exec(info);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
<<<<<<< Updated upstream
			if (WIFEXITED(status)) //Verifica se o processo terminou normalmente
				exit_status = WEXITSTATUS(status); //Obtém o código de saída (o valor passado para exit() ou retornado pelo main()).
			set_signals(); // Restore SIGINT handling after child exits
=======
			signal(SIGINT, handle_sigint);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (Core dumped)\n", 19);
			else
				write (1, "\n", 1);		
>>>>>>> Stashed changes
		}
	}
}

void	exec(t_info *info)
{
	char	*path;

	if (!info)
		return ;
	path = find_path(info);
	if (!path)
	{
		ft_putstr_fd(info->cmd_tree->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->cmd_tree->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		exit(127);
	}
	if (execve(path, info->cmd_tree->args, info->my_env) == -1)
	{
		ft_putstr_fd(info->cmd_tree->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_arr(info->cmd_tree->args);
		free_arr(info->my_env);
		free_builtins(info->builtins);
		free(path);
		exit(126);
	}
}
