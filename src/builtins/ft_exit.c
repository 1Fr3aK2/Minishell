/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:36 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/18 03:20:10 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strisnum(char *str)
{
	size_t	count;

	count = 0;
	if (!str || (!ft_isdigit(str[count]) && str[count] != '-'
			&& str[count] != '+'))
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

static int	validate_exit_args(t_info *info, char **args)
{
	if (args[2] && ft_strisnum(args[1]))
	{
		ft_putstr_fd("exit\nshellinho: exit: too many arguments\n", 2);
		update_status(info, 1);
		return (1);
	}
	if (!ft_strisnum(args[1]))
	{
		ft_putstr_fd("exit\nshellinho: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		update_status(info, 2);
		exit(info->exit_status);
	}
	return (0);
}

static int	parse_exit_args(t_info *info, int *exit_flags)
{
	if (info->cmd_tree && info->cmd_tree->args && info->cmd_tree->args[0])
	{
		if (ft_strncmp(info->cmd_tree->args[0], "exit", 5) == 0)
		{
			if (info->cmd_tree->args[1])
			{
				if (validate_exit_args(info, info->cmd_tree->args))
					return (0);
				*exit_flags = ft_atoi(info->cmd_tree->args[1]);
			}
			return (1);
		}
	}
	return (0);
}

void	ft_exit(t_info *info)
{
	int	exit_flags;
	int	has_valid_args;

	exit_flags = 0;
	has_valid_args = parse_exit_args(info, &exit_flags);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (has_valid_args)
		info->exit_status = exit_flags % 256;
	free_tree(info->cmd_tree);
	free_builtins(info->builtins);
	free_arr(info->my_env);
	free_arr(info->export_env);
	rl_clear_history();
	close_fds(0);
	free(info->io);
	free(info->types);
	free(info->redirections);
	exit(info->exit_status);
}

void	ft_exit2(t_info *info)
{
	free_tree(info->cmd_tree);
	free_builtins(info->builtins);
	free_arr(info->my_env);
	free_arr(info->export_env);
	free(info->io);
	free(info->types);
	free(info->redirections);
	rl_clear_history();
	close_fds(0);
	exit(info->exit_status);
}
