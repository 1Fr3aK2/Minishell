/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/06 18:08:24 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

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

static int	validate_exit_args(char **args)
{
	int	j;

	j = 0;
	if (args[2] && ft_strisnum(args[1]))
	{
		ft_putstr_fd("exit\nshellinho: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	while (args[1][j])
	{
		if (!ft_isdigit(args[1][j]))
		{
			ft_putstr_fd("exit\nshellinho: exit:", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			g_exit_status = 2;
			exit(g_exit_status);
		}
		j++;
	}
	return (0);
}

void	ft_exit(t_info *info)
{
	int	exit_flags;

	exit_flags = ft_atoi(info->flags);
	if (info->cmd_tree && info->cmd_tree->args && info->cmd_tree->args[1])
		if (validate_exit_args(info->cmd_tree->args))
			return ;
	if (isatty(STDIN_FILENO))
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
