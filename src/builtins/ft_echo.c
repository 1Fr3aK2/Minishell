/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:28:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/23 20:16:28 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flags(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_info *info)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (check_redirections(info) == 0)
		exit(0);
	while (check_flags(info->cmd_tree->args[i]) == 0)
		++i;
	while (info->cmd_tree->args[i])
	{
		while (info->cmd_tree->args[i][j])
		{
			write(1, &info->cmd_tree->args[i][j], 1);
			j++;
		}
		if ((info->cmd_tree->args[i + 1]))
			write(1, " ", 1);
		j = 0;
		i++;
	}
	if (check_flags(info->cmd_tree->args[1]) == 1)
		write(1, "\n", 1);
}


void ft_echo_wrapper(t_info *info, t_tree *node)
{
	int	i;
	int	j;

	i = 1;
	j = 0;

	if (check_redirections(info) == 0)
		exit(0);
	while (check_flags(node->args[i]) == 0)
		++i;
	while (node->args[i])
	{
		j = 0;
		while (node->args[i][j])
		{
			write(1, &node->args[i][j], 1);
			j++;
		}
		if (node->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (check_flags(node->args[1]) == 1)
		write(1, "\n", 1);
}