/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/15 19:44:10 by rafael           ###   ########.fr       */
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
    if (info->cmd_tree->args[i])
    {
        j = 0;
        if (info->cmd_tree->args[2] && ft_strisnum(info->cmd_tree->args[1]))
        {
            printf("exit\nshellinho: exit: too many arguments\n");
            exit_status = 1;
            return;
        }
        while (info->cmd_tree->args[i][j] != '\0')
        {
            if (!ft_isdigit(info->cmd_tree->args[i][j]))
            {
                printf("exit\nshellinho: exit: %s: numeric argument required\n", info->cmd_tree->args[i]);
                exit_status = 2;
                return;
            }
            j++;
        }
    }
	if (isatty(STDIN_FILENO)) // checks if stdin is connected to a terminal. Ex: in input redirections, stdin is connected to a file
		printf("exit\n");
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
