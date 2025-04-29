/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/29 16:43:59 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// sai do processo filo dentro de pipes cat Markefile | exit || CORRIGIT CTRL + D

static int	ft_strisnum(char *str)
{
	size_t	count;

	count = 0;
	if (!ft_isdigit(str[count]) && str[count] != '-' && str[count] != '+')
		return (0);
	count++;
	while (str[count])
	{
		if (!ft_isdigit(str[count]))
			return (0);
		count++;
	}
	return (1);
}

void	ft_exit(t_info *info)
{
	int	exit_flags;
    int i;
    int j;

	exit_flags = ft_atoi(info->flags);
    i = 1;
    if (info->cmd_tree && info->cmd_tree->args && info->cmd_tree->args[i])
    {
        j = 0;
        if (info->cmd_tree->args[2] && ft_strisnum(info->cmd_tree->args[1]))
        {
            ft_putstr_fd("exit\nshellinho: exit: too many arguments\n", 2);
            g_exit_status = 1;
            return;
        }
        while (info->cmd_tree->args[i][j] != '\0')
        {
            if (!ft_isdigit(info->cmd_tree->args[i][j]))
            {
				ft_putstr_fd("exit\nshellinho: exit:", 2);
                ft_putstr_fd(info->cmd_tree->args[i], 2);
				ft_putstr_fd(" numeric argument required\n", 2);
                g_exit_status = 2;
                exit(g_exit_status);
            }
            j++;
        }
    }
	if (isatty(STDIN_FILENO)) // checks if stdin is connected to a terminal. Ex: in input redirections, stdin is connected to a file
		printf("exit\n");
	if (exit_flags)
	{
		if (exit_flags > 255)
			g_exit_status = exit_flags % 256;
		else
			g_exit_status = exit_flags;
	}
	free_tree(info->cmd_tree);
	free_builtins(info->builtins);
	free_arr(info->my_env);
	free_arr(info->export_env);
	rl_clear_history();
	close_fds(0);
	exit(g_exit_status);
}
